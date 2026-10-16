"""Offline comparison of supplied Y540 PnP captures; never accesses hardware.

Example: python tools/compare_case_snapshots.py --case-dir C:/path/to/KeyboardFirmware-Issue
Uses the capture State field rather than assuming filename timestamps are capture times.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import subprocess


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest().upper()


def identity(device: dict) -> str:
    return str(device.get("InstanceId", "")).upper()


def prop(device: dict, name: str):
    return device.get("Properties", {}).get("DEVPKEY_Device_" + name)


def compact(device: dict) -> dict:
    return {"instance_id": device.get("InstanceId"), "name": device.get("FriendlyName"),
            "class": device.get("Class"), "present": device.get("Present"),
            "status": device.get("Status"), "problem": device.get("Problem"),
            "parent": prop(device, "Parent"), "location_info": prop(device, "LocationInfo"),
            "location_paths": prop(device, "LocationPaths"),
            "hardware_ids": prop(device, "HardwareIds"),
            "compatible_ids": prop(device, "CompatibleIds"),
            "bus_description": prop(device, "BusReportedDeviceDesc"),
            "driver_provider": prop(device, "DriverProvider"),
            "driver_version": prop(device, "DriverVersion")}


def parent_chain(device: dict, devices: dict) -> list[dict]:
    result, seen = [], set()
    current = device
    while current and identity(current) not in seen:
        seen.add(identity(current))
        result.append(compact(current))
        parent = prop(current, "Parent")
        current = devices.get(str(parent).upper()) if parent else None
    return result


def load_case(case_dir: Path) -> tuple[dict, dict]:
    captures, source_paths = {}, {}
    for path in sorted(case_dir.glob("*.json")):
        data = json.loads(path.read_text(encoding="utf-8-sig"))
        state = data.get("Capture", {}).get("State")
        if state in ("working", "failed"):
            if state in captures:
                raise ValueError(f"Multiple {state} snapshots: choose a directory with exactly one pair")
            if not isinstance(data.get("Devices"), list):
                raise ValueError(f"{path.name} lacks Devices array")
            captures[state], source_paths[state] = data, path
    if set(captures) != {"working", "failed"}:
        raise ValueError("Need one working and one failed snapshot")
    return captures, source_paths


def matching_failed_devices(known: dict, devices: list[dict]) -> list[dict]:
    """Candidates only: historical snapshot topology does not authorize live changes."""
    if not identity(known).startswith("USB\\VID_048D&PID_C100\\"):
        return []
    parent, location = prop(known, "Parent"), prop(known, "LocationInfo")
    if not parent or not location:
        return []
    suffix = identity(known).rsplit("\\", 1)[-1]
    matches = []
    for device in devices:
        hardware_ids = {str(i).upper() for i in (prop(device, "HardwareIds") or [])}
        if (identity(device).startswith("USB\\VID_0000&PID_0002\\")
                and device.get("Present") is True and device.get("Problem") == 43
                and "USB\\DEVICE_DESCRIPTOR_FAILURE" in hardware_ids
                and str(prop(device, "Parent")).upper() == str(parent).upper()
                and str(prop(device, "LocationInfo")).upper() == str(location).upper()
                and identity(device).rsplit("\\", 1)[-1] == suffix):
            matches.append(device)
    return matches


def compare(case_dir: Path) -> dict:
    captures, paths = load_case(case_dir)
    indexes = {state: {identity(d): d for d in data["Devices"]} for state, data in captures.items()}
    known = [d for d in captures["working"]["Devices"]
             if identity(d).startswith("USB\\VID_048D&PID_C100\\")
             and d.get("Present") is True and d.get("Problem") == 0]
    candidates = matching_failed_devices(known[0], captures["failed"]["Devices"]) if len(known) == 1 else []
    sections = ("Computer", "BIOS", "OperatingSystem", "Battery", "FastStartup", "Power")
    diffs = []
    for instance in sorted(set(indexes["working"]) | set(indexes["failed"])):
        wd, fd = indexes["working"].get(instance), indexes["failed"].get(instance)
        if wd != fd:
            # Compare all field values, including case-only string differences.
            field_diffs = {}
            for field in sorted(set(wd or {}) | set(fd or {})):
                if (wd or {}).get(field) != (fd or {}).get(field):
                    field_diffs[field] = {"working": (wd or {}).get(field), "failed": (fd or {}).get(field)}
            diffs.append({"instance_id": instance, "working": compact(wd) if wd else None,
                          "failed": compact(fd) if fd else None, "changed_fields": field_diffs})
    target_re = ("VID_048D&PID_C100", "VID_048D&PID_89DB", "VID_0000&PID_0002")
    artifacts = []
    for path in sorted(case_dir.rglob("*")):
        if not path.is_file():
            continue
        item = {"relative_path": path.relative_to(case_dir).as_posix(),
                "bytes": path.stat().st_size, "sha256": sha256(path)}
        if path.suffix.lower() in (".zip", ".rar"):
            listing = subprocess.run(["tar", "-tf", str(path)], capture_output=True, text=True,
                                     encoding="utf-8", errors="replace", check=False)
            item["archive_inventory"] = {"tool": "tar -tf", "return_code": listing.returncode,
                                         "members": listing.stdout.splitlines(), "stderr": listing.stderr}
        artifacts.append(item)
    return {"schema": "y540-case-comparison-v1", "scope": "Offline JSON and file inventory only; no hardware or installer execution",
            "sources": {state: {"filename": paths[state].name, "sha256": sha256(paths[state]),
                                "capture": data["Capture"], "device_count": len(data["Devices"]),
                                "all_devices_parsed": True}
                        for state, data in captures.items()},
            "system_sections": {name: {"equal": captures["working"].get(name) == captures["failed"].get(name),
                                        "working": captures["working"].get(name), "failed": captures["failed"].get(name)}
                                for name in sections},
            "relevant_devices": {state: [compact(d) for d in data["Devices"]
                                          if any(token in identity(d) for token in target_re)]
                                 for state, data in captures.items()},
            "working_keyboard_parent_chain": parent_chain(known[0], indexes["working"]) if len(known) == 1 else [],
            "historical_failed_candidate_selection": {
                "known_present_c100_count": len(known), "candidate_count": len(candidates),
                "unambiguous": len(known) == 1 and len(candidates) == 1,
                "candidates": [compact(d) for d in candidates],
                "criteria": ["historically present USB VID048D/PIDC100 normal devnode with problem0",
                             "present USB VID0000/PID0002 devnode with problem43 and USB DEVICE_DESCRIPTOR_FAILURE hardware id",
                             "same exact parent (case insensitive), same nonempty LocationInfo, same instance suffix",
                             "exactly one known normal device and exactly one matching failed devnode"],
                "limitations": ["LocationPaths were not captured; never invented from port strings",
                                "Placeholder VID/PID has no authenticated ITE device identity",
                                "Historical candidate is not permission or sufficient evidence to mutate a live device",
                                "Live implementation must read fresh properties, retain parent/location match, and fail closed on ambiguity",
                                "Port_#0009 or error43 alone must never select a device"]},
            "all_device_differences": diffs,
            "events": {state: data.get("RecentSystemEvents", []) for state, data in captures.items()},
            "artifact_inventory": artifacts}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--case-dir", type=Path, required=True)
    parser.add_argument("--output", type=Path, default=Path("evidence/case-comparison.json"))
    args = parser.parse_args()
    result = compare(args.case_dir)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(f"Wrote {args.output}; parsed {sum(s['device_count'] for s in result['sources'].values())} devices; "
          f"{result['historical_failed_candidate_selection']['candidate_count']} historical failed candidate(s)")


if __name__ == "__main__":
    main()
