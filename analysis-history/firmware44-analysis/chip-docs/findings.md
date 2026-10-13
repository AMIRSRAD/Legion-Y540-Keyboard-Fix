# Controller identity and register-documentation boundary

Reviewed 2026-10-12. This is passive artifact/document research; no hardware operations were performed.

## Local evidence

The supplied `Board/Lenovo Legion Y540-15IRH - NM-C221 REV0.1 Boardview.rar` contains one main-board TVW and seven daughter-board TVWs, plus two pictures and an origin text file. It contains no datasheet or register manual. Main-board TVW ASCII strings include:

| String | First file offset | Meaning established by this pass |
|---|---:|---|
| `IT8176FN-56A-BX_QFN48_6X6` | `0x11C06EB` | This exact controller part/package is named in the supplied board artifact. |
| `IT8226E-128-BX_LQFP128_14X14` | `0x11F10A8` | A distinct controller is also named. |
| `USB20_N9_AGKB` / `USB20_P9_AGKB` | `0x11824AF` / `0x11824BD` | Board net-name strings consistent with a USB pair numbered 9. |
| `AG_WRST#` | `0x11827DB` | Reset-looking net name; function/polarity/electrical timing not verified. |
| `AGKB_PWR_EN#` | `0x11827E4` | Power-enable-looking net name; electrical behavior not verified. |
| `AGKB_PWR_OCB` | `0x11827FB` | Another power-related name; meaning not verified. |

Exact file identity and all occurrence offsets are in `local-board-evidence.json`. These are strings extracted from a proprietary boardview; this pass did not decode pin-to-net connectivity or component designators. The affected owner's physical board revision has not been verified. Therefore this supports IT8176-family identity for the supplied reference board, but cannot prove that every Y540 or the affected laptop uses that exact suffix.

Existing firmware descriptor evidence names the product `ITE Device(8910)` while normal VID/PID is `048D:C100`. A USB product string is firmware-controlled text, not a physical silicon identification. The updater INI's `BOOTDEVICECHIPID=8171` likewise must not override the board artifact's IT8176 label or be interpreted as an independently measured chip marking.

## Primary-source search

Bounded searches used `site:ite.com.tw IT8176`, `IT8171`, exact FN suffixes, and USB/register terms. No public IT8176/IT8171 USB reset, suspend, clock, watchdog or startup register specification was obtained. This is a search result, not proof none exists or that an NDA is universally required.

ITE publishes other controller descriptions, for example [IT8987](https://www.ite.com.tw/tw/product/cate2/IT8987) and [IT82302 preliminary specification](https://www.ite.com.tw/upload/2024_01_23/6_2024012316175049je5fzt61.pdf). These are different parts. The [Zephyr IT8XXX2 documentation](https://docs.zephyrproject.org/latest/boards/ite/it8xxx2_evb/doc/index.html) and [IT82XX2 USB binding](https://docs.zephyrproject.org/latest/build/dts/api/bindings/usb/ite%2Cit82xx2-usb.html) are also for different families. Their memory maps are not a justified substitute for this 8051-family payload.

The verified Lenovo package metadata is [ite1fw11s_y540](https://download.lenovo.com/consumer/mobiles/ite1fw11s_y540_2_.xml), retained locally in the case repository. It identifies keyboard firmware 00000044 but does not provide internal register documentation.

## Implication for firmware analysis

Trace firmware control flow, XDATA addresses and bit operations as observed operations until a register's identity is established through converging evidence. Do not label an arbitrary MMIO write as USB reset, suspend-clear, pull-up control or watchdog solely because a related ITE family uses that address. Likewise, do not propose a persistent firmware patch using guessed reset bits.

The board strings provide useful leads for a later qualified electrical investigation: reference-board power-enable/reset paths are plausible points to examine when forced power-off recovers a retained-state fault. They do not establish which path is defective, or prove that firmware44 contains an error.
