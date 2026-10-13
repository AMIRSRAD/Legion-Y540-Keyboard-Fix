# Matching fix1 logs against the USB trace

All four files supplied in `Desktop/New folder (2)` were read in full. Three contain data; the fourth is zero bytes. Three complete inventories contain 34 records each, totaling 102 device records. File sizes, SHA-256 digests, parsed device fields, complete logged event messages, comparisons, and selected USB events are saved in `fix1-correlation.json`.

**Result: the recorded fix1 USB retry coincides with real keyboard re-enumeration, but fails to restore communication.** This closes the action-correlation gap in the earlier trace report. There is no recorded firmware write.

| Tehran time, 12 October 2026 | Evidence |
|---|---|
| 17:20:52.516 | Diagnose inventory: AC connected, battery 95%; keyboard descriptor-failure placeholder present with problem 43; normal C100 device and five HID children nonpresent. |
| 17:20:56.122 | Before-retry inventory: all 34 device records identical to Diagnose. |
| 17:21:00.037 | fix1 logs its one nonpersistent USB devnode restart attempt. |
| 17:21:00.047883 | USBHUB3 starts enumeration on port 9, approximately 11 ms after the attempt message. |
| 17:21:00.048 | fix1 reports Windows accepted the restart. |
| 17:21:00.135992–17:21:02.105221 | Four GET_DESCRIPTOR(Device) completions fail with USBD_STATUS_XACT_ERROR (0xC0000011), each returning zero bytes. |
| 17:21:02.105687 | HUB3 reports port 9 enumeration failure. |
| 17:21:03.186 | After-retry inventory: all 34 device records still identical to the two earlier inventories; descriptor failure remains. |
| 17:21:33.279 | Filename of fourth log; file is empty. Its name is not evidence that a later diagnosis completed. |

ETW UTC times above were reconstructed from trace-header StartTime FILETIME plus displayed event-to-header clock differences, avoiding tracerpt's inconsistent rendered +03:29 offset. They agree closely with fix1's independently logged UTC messages. Conversion to Tehran uses UTC+03:30. Sub-millisecond digits reflect trace timestamps, not certainty about causality at that precision.

## Device selection and wider activity

The only eligible recovery candidate in the before-state is the exact failed instance `USB\VID_0000&PID_0002\5&1F456139&0&9`, on `Port_#0009.Hub_#0002`, parent `USB\ROOT_HUB30\4&15ED8360&0&0`. fix1 source requires exactly one eligible candidate and operates on that selected instance. The log does not explicitly print the chosen ID at the API call, so selection is supported by the inventory plus reviewed source rather than a dedicated API-call target record.

The owner reports using only Diagnose and USB retry, with no AC changes or Device Manager actions. Port 6 device 30C9:001B reconnects twice during the same burst and successfully enumerates each time. This is still unexplained. The retry source contains no explicit parent-hub/controller restart. Temporal association is strong; the trace does not prove what caused the other port to reconnect or identify a shared hardware defect.

## What follows from this

The Windows request was accepted and fresh keyboard enumeration occurred; this was not merely an unchanged cached Device Manager display. The device cannot complete the basic descriptor exchange in this failed state, before its normal HID interface becomes usable. Changing updater HID matching or bypassing its not-found result cannot by itself establish that missing communication.

This evidence does not identify whether keyboard firmware, BIOS/EC sequencing, host USB behavior, or an electrical condition causes the failure. It does not prove permanent damage or that another firmware flash would help. Earlier successful operation after a battery cold start remains important evidence that the device can work under another startup condition.

The next discriminating comparison is the same capture after the known successful battery cold start, with AC kept unchanged throughout the recording: Diagnose, USB retry once, wait ten seconds, Diagnose, finish recording. Use the existing external input because retry can interrupt the working keyboard. Record whether typing returns after retry. Supply both the finished recording ZIP and its fix1 logs. This tests whether the same operation succeeds in the healthy state and whether the port 6 activity is reproducible there. No firmware writing is needed for this comparison. If typing fails during this test, stop further retries and preserve the recording.

Original source and release builds were not modified by this analysis.
