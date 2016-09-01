//@date:2016.9.1
//@author:yangjie82@gmail.com
//@brief:platform detail for device
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct DevicePlatform {
  HWND      mainWindow;
  WNDCLASS  windowClass;
  TCHAR*    windowClassName;
};