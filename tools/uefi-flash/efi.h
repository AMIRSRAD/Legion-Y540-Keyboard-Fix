/* Minimal UEFI definitions (subset of the UEFI 2.x spec) for a freestanding build. */
#pragma once
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef UINT64 UINTN;
typedef unsigned short CHAR16;
typedef unsigned char BOOLEAN;
typedef UINTN EFI_STATUS;
typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
#define EFIAPI __attribute__((ms_abi))
#define EFI_SUCCESS 0
#define EFI_ERR(x) (0x8000000000000000ULL | (x))
#define EFI_NOT_FOUND EFI_ERR(14)
#define EFI_ERROR(s) (((long long)(s)) < 0)

typedef struct { UINT32 d1; UINT16 d2, d3; UINT8 d4[8]; } EFI_GUID;
typedef struct { UINT64 Signature; UINT32 Revision, HeaderSize, CRC32, Reserved; } EFI_TABLE_HEADER;

typedef struct { UINT16 ScanCode; CHAR16 UnicodeChar; } EFI_INPUT_KEY;
typedef struct EFI_SIMPLE_TEXT_INPUT {
  EFI_STATUS (EFIAPI *Reset)(struct EFI_SIMPLE_TEXT_INPUT *, BOOLEAN);
  EFI_STATUS (EFIAPI *ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT *, EFI_INPUT_KEY *);
  EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT;

typedef struct EFI_SIMPLE_TEXT_OUTPUT {
  void *Reset;
  EFI_STATUS (EFIAPI *OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT *, CHAR16 *);
  void *TestString, *QueryMode, *SetMode;
  EFI_STATUS (EFIAPI *SetAttribute)(struct EFI_SIMPLE_TEXT_OUTPUT *, UINTN);
  EFI_STATUS (EFIAPI *ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT *);
  void *SetCursorPosition, *EnableCursor, *Mode;
} EFI_SIMPLE_TEXT_OUTPUT;

typedef enum { AllHandles, ByRegisterNotify, ByProtocol } EFI_LOCATE_SEARCH_TYPE;

typedef struct {
  EFI_TABLE_HEADER Hdr;
  void *RaiseTPL, *RestoreTPL;
  void *AllocatePages, *FreePages, *GetMemoryMap;
  EFI_STATUS (EFIAPI *AllocatePool)(UINTN PoolType, UINTN Size, void **Buffer);
  EFI_STATUS (EFIAPI *FreePool)(void *Buffer);
  void *CreateEvent, *SetTimer;
  EFI_STATUS (EFIAPI *WaitForEvent)(UINTN, EFI_EVENT *, UINTN *);
  void *SignalEvent, *CloseEvent, *CheckEvent;
  void *InstallProtocolInterface, *ReinstallProtocolInterface, *UninstallProtocolInterface;
  EFI_STATUS (EFIAPI *HandleProtocol)(EFI_HANDLE, EFI_GUID *, void **);
  void *Reserved, *RegisterProtocolNotify;
  void *LocateHandle, *LocateDevicePath, *InstallConfigurationTable;
  void *LoadImage, *StartImage, *Exit, *UnloadImage, *ExitBootServices;
  void *GetNextMonotonicCount;
  EFI_STATUS (EFIAPI *Stall)(UINTN Microseconds);
  EFI_STATUS (EFIAPI *SetWatchdogTimer)(UINTN, UINT64, UINTN, CHAR16 *);
  EFI_STATUS (EFIAPI *ConnectController)(EFI_HANDLE, EFI_HANDLE *, void *, BOOLEAN);
  void *DisconnectController;
  void *OpenProtocol, *CloseProtocol, *OpenProtocolInformation;
  void *ProtocolsPerHandle;
  EFI_STATUS (EFIAPI *LocateHandleBuffer)(EFI_LOCATE_SEARCH_TYPE, EFI_GUID *, void *, UINTN *, EFI_HANDLE **);
  EFI_STATUS (EFIAPI *LocateProtocol)(EFI_GUID *, void *, void **);
} EFI_BOOT_SERVICES;

typedef struct {
  EFI_TABLE_HEADER Hdr;
  CHAR16 *FirmwareVendor;
  UINT32 FirmwareRevision;
  EFI_HANDLE ConsoleInHandle;
  EFI_SIMPLE_TEXT_INPUT *ConIn;
  EFI_HANDLE ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT *ConOut;
  EFI_HANDLE StandardErrorHandle;
  EFI_SIMPLE_TEXT_OUTPUT *StdErr;
  void *RuntimeServices;
  EFI_BOOT_SERVICES *BootServices;
} EFI_SYSTEM_TABLE;

typedef struct {
  UINT32 Revision;
  EFI_HANDLE ParentHandle;
  EFI_SYSTEM_TABLE *SystemTable;
  EFI_HANDLE DeviceHandle;
} EFI_LOADED_IMAGE;

typedef struct EFI_FILE {
  UINT64 Revision;
  EFI_STATUS (EFIAPI *Open)(struct EFI_FILE *, struct EFI_FILE **, CHAR16 *, UINT64, UINT64);
  EFI_STATUS (EFIAPI *Close)(struct EFI_FILE *);
  EFI_STATUS (EFIAPI *Delete)(struct EFI_FILE *);
  EFI_STATUS (EFIAPI *Read)(struct EFI_FILE *, UINTN *, void *);
  EFI_STATUS (EFIAPI *Write)(struct EFI_FILE *, UINTN *, void *);
  void *GetPosition;
  EFI_STATUS (EFIAPI *SetPosition)(struct EFI_FILE *, UINT64);
  void *GetInfo, *SetInfo;
  EFI_STATUS (EFIAPI *Flush)(struct EFI_FILE *);
} EFI_FILE;
#define EFI_FILE_MODE_READ 1ULL
#define EFI_FILE_MODE_WRITE 2ULL
#define EFI_FILE_MODE_CREATE 0x8000000000000000ULL

typedef struct EFI_SIMPLE_FILE_SYSTEM {
  UINT64 Revision;
  EFI_STATUS (EFIAPI *OpenVolume)(struct EFI_SIMPLE_FILE_SYSTEM *, EFI_FILE **);
} EFI_SIMPLE_FILE_SYSTEM;

typedef struct { UINT8 Type, SubType; UINT8 Length[2]; } EFI_DEVICE_PATH;
typedef struct {
  void *ConvertDeviceNodeToText;
  CHAR16 *(EFIAPI *ConvertDevicePathToText)(EFI_DEVICE_PATH *, BOOLEAN, BOOLEAN);
} EFI_DEVICE_PATH_TO_TEXT;

#pragma pack(push, 1)
typedef struct { UINT8 RequestType, Request; UINT16 Value, Index, Length; } EFI_USB_DEVICE_REQUEST;
typedef struct {
  UINT8 Length, DescriptorType; UINT16 BcdUSB; UINT8 DeviceClass, DeviceSubClass, DeviceProtocol, MaxPacketSize0;
  UINT16 IdVendor, IdProduct, BcdDevice; UINT8 StrManufacturer, StrProduct, StrSerialNumber, NumConfigurations;
} EFI_USB_DEVICE_DESCRIPTOR;
typedef struct {
  UINT8 Length, DescriptorType, InterfaceNumber, AlternateSetting, NumEndpoints;
  UINT8 InterfaceClass, InterfaceSubClass, InterfaceProtocol, Interface;
} EFI_USB_INTERFACE_DESCRIPTOR;
#pragma pack(pop)
typedef enum { EfiUsbDataIn, EfiUsbDataOut, EfiUsbNoData } EFI_USB_DATA_DIRECTION;

typedef struct EFI_USB_IO {
  EFI_STATUS (EFIAPI *UsbControlTransfer)(struct EFI_USB_IO *, EFI_USB_DEVICE_REQUEST *, EFI_USB_DATA_DIRECTION,
                                          UINT32 TimeoutMs, void *Data, UINTN DataLength, UINT32 *Status);
  void *UsbBulkTransfer, *UsbAsyncInterruptTransfer, *UsbSyncInterruptTransfer;
  void *UsbIsochronousTransfer, *UsbAsyncIsochronousTransfer;
  EFI_STATUS (EFIAPI *UsbGetDeviceDescriptor)(struct EFI_USB_IO *, EFI_USB_DEVICE_DESCRIPTOR *);
  void *UsbGetConfigDescriptor;
  EFI_STATUS (EFIAPI *UsbGetInterfaceDescriptor)(struct EFI_USB_IO *, EFI_USB_INTERFACE_DESCRIPTOR *);
  void *UsbGetEndpointDescriptor;
  EFI_STATUS (EFIAPI *UsbGetStringDescriptor)(struct EFI_USB_IO *, UINT16 LangId, UINT8 StringId, CHAR16 **String);
  void *UsbGetSupportedLanguages;
  void *UsbPortReset;
} EFI_USB_IO;
