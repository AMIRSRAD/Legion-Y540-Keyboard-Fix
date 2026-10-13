
bool GetHIDDevicePath(int UsbstorNum,AnsiString *Path)

{
  BOOL BVar1;
  HDEVINFO DeviceInfoSet;
  AnsiStringT<0> local_a0;
  PSP_INTERFACE_DEVICE_DETAIL_DATA pDevInfoDetail;
  DWORD ReqLen;
  SP_INTERFACE_DEVICE_DATA DevInfoData;
  HDEVINFO hDevInfo;
  GUID GUID_DEVINTERFACE_HID;
  AnsiString *Path_local;
  int UsbstorNum_local;
  bool local_41;
  
  HidD_GetHidGuid(&GUID_DEVINTERFACE_HID);
  DeviceInfoSet = SetupDiGetClassDevsA((GUID *)&GUID_DEVINTERFACE_HID,(PCSTR)0x0,(HWND)0x0,0x12);
  DevInfoData.cbSize = 0x20;
  BVar1 = SetupDiEnumDeviceInterfaces
                    (DeviceInfoSet,(PSP_DEVINFO_DATA)0x0,(GUID *)&GUID_DEVINTERFACE_HID,UsbstorNum,
                     (PSP_DEVICE_INTERFACE_DATA)&DevInfoData);
  if (BVar1 == 0) {
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
    local_41 = false;
  }
  else {
    SetupDiGetDeviceInterfaceDetailA
              (DeviceInfoSet,(PSP_DEVICE_INTERFACE_DATA)&DevInfoData,
               (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)0x0,0,&ReqLen,(PSP_DEVINFO_DATA)0x0);
    pDevInfoDetail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)_Znay(ReqLen);
    if (pDevInfoDetail == (PSP_INTERFACE_DEVICE_DETAIL_DATA)0x0) {
      SetupDiDestroyDeviceInfoList(DeviceInfoSet);
      local_41 = false;
    }
    else {
      ((PSP_DEVICE_INTERFACE_DETAIL_DATA_A)pDevInfoDetail)->cbSize = 8;
      BVar1 = SetupDiGetDeviceInterfaceDetailA
                        (DeviceInfoSet,(PSP_DEVICE_INTERFACE_DATA)&DevInfoData,
                         (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)pDevInfoDetail,ReqLen,(PDWORD)0x0,
                         (PSP_DEVINFO_DATA)0x0);
      if (BVar1 == 0) {
        SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        if (pDevInfoDetail != (PSP_INTERFACE_DEVICE_DETAIL_DATA)0x0) {
          _ZdlPv(pDevInfoDetail);
        }
        local_41 = false;
      }
      else {
        local_a0.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
        _ZN6System14AnsiStringBaseC2EPKci(&local_a0,pDevInfoDetail->DevicePath,0);
        _ZN6System14AnsiStringBaseaSERKS0_(Path,&local_a0);
        System::AnsiStringT<0>::~AnsiStringT(&local_a0);
        SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        if (pDevInfoDetail != (PSP_INTERFACE_DEVICE_DETAIL_DATA)0x0) {
          _ZdlPv(pDevInfoDetail);
        }
        local_41 = true;
      }
    }
  }
  return local_41;
}

