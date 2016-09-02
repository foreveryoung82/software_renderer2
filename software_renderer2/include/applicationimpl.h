//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:application detail
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct ApplicationImpl {
  HWND      mainWindow;
  WNDCLASS  windowClass;
  TCHAR*    windowClassName;
  HDC       memoryDC;
  void*     bytes;
};