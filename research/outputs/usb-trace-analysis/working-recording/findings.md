# Working and failed USB recordings compared

**The working recording contains successful live transfers from the same keyboard that fails USB enumeration in the AC-startup case. No permanent repair is established.** The working retry was refused, so these recordings do not compare two completed resets.

## Capture validation

The supplied `recording-20261012T141255304Z.zip` was finalized successfully. Its journal records a 180.1-second observation window and successful stop/deletion of the owned trace session. The ETL is 262,144 bytes. Offline tracerpt decoded 653 events across four buffers with zero events or buffers lost. One schema error (15005) affects metadata PartitionInfoExtensionV2, ordinal 1; no USB-provider record reports a schema error. File hashes, selected evidence, and comparisons are in `comparison.json`; raw XML and all 653 parsed events are preserved alongside it.

The journal's fixed text says “keyboard already failing.” That is a template scenario label, not a measured keyboard state. The supplied fix1 inventories and owner report establish this as the working-state test. Likewise, the capture script's statement that it performs no restart refers to the script itself; fix1 separately attempted its manually requested action.

## Evidence comparison

| Observation | Failed recording | Working recording |
|---|---|---|
| Measured power in matching fix1 logs | AC connected | Battery |
| Retry result in matching fix1 logs | Windows accepted | Refused: CR_NOT_DISABLEABLE, 40 |
| Port 9 state | Descriptor-failure placeholder | Normal 048D:C100, revision 0044 |
| Fresh descriptor attempts during recording | Four, all transaction failures, zero bytes | None captured |
| Live keyboard data transfers | Normal keyboard interface unavailable | Four successful 33-byte completions |
| Port 6 device 30C9:001B reconnections | Two, followed by successful enumeration | None captured |
| Lost trace events | Zero | Zero |

Working HUB3 rundown event ordinal 643 identifies Intel controller 8086:A36D at 00:14.0, port 9, instance `USB\VID_048D&PID_C100\5&1f456139&0&9`, with a nonzero device object `0x7BF2BFD94538`. It records device-descriptor length 18/type 1, USB 1.10, endpoint-zero maximum packet size 64, revision 0044, one configuration, configuration descriptor length 34, and Suspended=0. These are a snapshot of an already enumerated device; they are not fresh descriptor responses in this recording or a firmware-integrity check.

Four subsequent UCX event 27 completions (ordinals 645, 647, 649, 651) share that exact device object. Each reports URB status 0, IRP NTSTATUS 0, and actual transfer length 0x21 (33 bytes). They occur at approximately 17:43:52.380–17:43:52.880 Tehran time on 12 October 2026, after fix1 logged the refused disable at 17:43:49.074. These establish live successful keyboard USB traffic rather than merely cached identity. Each completion is followed by a dispatch for another transfer. Payloads were not captured, so particular keys or report contents cannot be inferred.

No HUB3 enumeration start/completion/retry/failure events, descriptor-request failures, port-change failures, or UCX control-transfer completions appear in the working trace. No events fall within two seconds of the logged retry time. This is consistent with the separately logged refused disable; it is not evidence that a physical reset happened silently or succeeded.

The matching working logs show all 34 device records unchanged across three inventories and the owner reports normal typing continued. The failed logs instead correlate accepted retry with fresh failed enumeration. The two calls act on different devnodes at the same physical port (failed placeholder versus normal C100). Consequently, absent port 6 reconnections in this working recording cannot distinguish a normal consequence of an accepted retry from a failure-specific platform effect.

## What this narrows down

The keyboard can enumerate correctly and deliver live data after a successful battery startup. In the failed AC-startup state, it cannot finish the basic USB device-descriptor exchange, before normal HID access. This supports investigating the startup-dependent initialization/power/reset boundary. It does not identify keyboard firmware, EC/BIOS, the host controller, or electrical hardware as the cause. Successful runtime traffic does not prove all firmware bytes are correct.

Both recordings begin after Windows has booted. Neither records the transition that first makes the keyboard fail. More repeats of the same refused/failed USB retry will not fill that gap. The next investigation should examine the boot/initialization boundary and available firmware/BIOS evidence, with any new capture designed to include that transition. This evidence provides no validated firmware patch and no reason to force a broader controller reset or repeat flashing.

No additional USB-retry test is requested on the basis of this comparison. Original source and build artifacts remain unchanged.

## Method limits

Event ordinals are zero-based XML order. UTC reconstruction uses trace-header FILETIME StartTime plus displayed event-to-header clock differences; tracerpt's inconsistent rendered +03:29 offset is retained as raw text and not used directly. Tehran display uses UTC+03:30. The capture selects USB headers/state events, not payload contents. Device pointers correlate records only within each recording and must not be compared across boots. Flattened JSON is a convenience; raw XML is authoritative for nested/repeated field names.
