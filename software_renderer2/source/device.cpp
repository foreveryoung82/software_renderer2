#include "device.h"
#include "deviceplatform.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

extern HINSTANCE happ;

LRESULT CALLBACK WndProc(HWND hwnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;
  RECT rect;

  switch(message) {
    case WM_PAINT:
      hdc=BeginPaint(hwnd,&ps);
      GetClientRect(hwnd,&rect);
      DrawText(hdc,
               TEXT("Hello,win98!"),
               -1,
               &rect,
               DT_SINGLELINE|DT_CENTER|DT_VCENTER);
      EndPaint(hwnd,&ps);
      return 0;
  }
  return DefWindowProc(hwnd,message,wParam,lParam);
}

void init_window_class(WNDCLASS* windowClass, const DevicePlatform& platform) {
  windowClass->style=CS_HREDRAW|CS_VREDRAW;
  windowClass->lpfnWndProc=WndProc;
  windowClass->cbClsExtra=0;
  windowClass->cbWndExtra=0;
  windowClass->hInstance=happ;
  windowClass->hIcon=LoadIcon(NULL,IDI_APPLICATION);
  //windowClass->hCursor=LoadIcon(NULL,IDC_ARROW);
  windowClass->hCursor=NULL;

  windowClass->hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
  windowClass->lpszMenuName=NULL;
  windowClass->lpszClassName=platform.windowClassName;
}

void register_window_class(const WNDCLASS* windowClass) {
  if (!RegisterClass(windowClass)) {
    MessageBox(NULL,
               TEXT("Register window class failed!"),
               TEXT("Error"),
               MB_ICONERROR);
  }
}

HWND create_window(const DevicePlatform& platform) {
  HWND hwnd=CreateWindow(platform.windowClassName,
                         TEXT("software_renderer"),
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         NULL,
                         NULL,
                         happ,
                         NULL);

  return hwnd;
}

Device::Device( const DeviceParameters& param )
 : param_(param),
  platform_(new DevicePlatform) {
  //ZeroMemory(&platform_,sizeof(DevicePlatform));
  platform_->windowClassName=TEXT("software_renderer_window_class");

  init_window_class(&platform_->windowClass, *platform_);
  register_window_class(&platform_->windowClass);
  platform_->mainWindow=create_window(*platform_);
  ShowWindow(platform_->mainWindow,SW_NORMAL);
  UpdateWindow(platform_->mainWindow);

  MSG msg;
  while (GetMessage(&msg,NULL,0,0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

Device::~Device() {
  delete platform_;
}

void Device::draw( const Triangle& shape ) {
}

void Device::clear() {
}

void Device::present() {
}
