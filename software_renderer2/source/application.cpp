#include "application.h"
#include <cassert>
#include <memory.h>
#include "applicationimpl.h"

static Application* s_application_instance=nullptr;

LRESULT CALLBACK WndProc(HWND hwnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {
  switch(message) {
    case WM_CREATE:
      return 0;
    case WM_PAINT:
      s_application_instance->fireOnFrameBeginEvent();
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(hwnd,message,wParam,lParam);
}

void init_window_class(WNDCLASS* windowClass, const TCHAR* windowClassName) {
  windowClass->style=CS_HREDRAW|CS_VREDRAW;
  windowClass->lpfnWndProc=WndProc;
  windowClass->cbClsExtra=0;
  windowClass->cbWndExtra=0;
  windowClass->hInstance=NULL;
  windowClass->hIcon=LoadIcon(NULL,IDI_APPLICATION);
  windowClass->hCursor=NULL;
  windowClass->hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
  windowClass->lpszMenuName=NULL;
  windowClass->lpszClassName=windowClassName;
}

void register_window_class(WNDCLASS* windowClass) {
  if (!RegisterClass(windowClass)) {
    MessageBox(NULL,
               TEXT("Register window class failed!"),
               TEXT("Error"),
               MB_ICONERROR);
  }
}

HWND create_window(TCHAR* windowClassName,int width,int height) {
  HWND hwnd=CreateWindow(
    windowClassName,
    TEXT("software_renderer"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    NULL,
    NULL);
  RECT rect={0,0,width,height};
  AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), FALSE);
  int win_width=rect.right-rect.left;
  int win_height=rect.bottom-rect.top;
  SetWindowPos(hwnd,
               NULL,
               0,
               0, 
               win_width,
               win_height,
               (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
  return hwnd;
}

HDC create_memory_dc(HWND hwnd) {
  HDC hdc=GetDC(hwnd);
  HDC memoryDC=CreateCompatibleDC(hdc);
  ReleaseDC(hwnd,hdc);

  return memoryDC;
}

HBITMAP create_dib(HDC memoryDC, void** bytes, int width, int height) {
  BITMAPINFO bitmap_info;
  memset(&bitmap_info,0,sizeof(BITMAPINFO));
  BITMAPINFOHEADER* header=&bitmap_info.bmiHeader;
  header->biSize=sizeof(BITMAPINFO);
  header->biWidth=width;
  header->biHeight=height;
  header->biPlanes=1;
  header->biBitCount=32;
  header->biCompression=BI_RGB;
  HBITMAP hbmp=CreateDIBSection(memoryDC,
                                &bitmap_info,
                                DIB_RGB_COLORS,
                                bytes,
                                NULL,
                                NULL);
  return hbmp;
} 

void select_dib_into_memory_dc(HDC memoryDC,HBITMAP hbmp) {
  SelectObject(memoryDC, hbmp);
}

Application::Application()
 : width_(0)
 , height_(0)
 , impl_(nullptr)
 , onFrameBeginEvent_() {
  assert(!s_application_instance);
  s_application_instance=this;
}

Application::~Application() {
  assert(s_application_instance);
  s_application_instance=nullptr;
}

void Application::setup(int width, int height) {
  assert(!impl_);

  width_=width;
  height_=height;
  impl_=new ApplicationImpl;
  impl_->windowClassName=TEXT("software render windows class");
  impl_->mainWindow=NULL;
  impl_->memoryDC=NULL;
  impl_->framebuffer=nullptr;
  memset(&impl_->windowClass,0,sizeof(WNDCLASS));
  
  init_window_class(&impl_->windowClass,impl_->windowClassName);
  register_window_class(&impl_->windowClass);
  impl_->mainWindow=create_window(impl_->windowClassName,width,height);
  impl_->memoryDC=create_memory_dc(impl_->mainWindow);
  HBITMAP hbmp=create_dib(impl_->memoryDC, &impl_->framebuffer, width, height);
  select_dib_into_memory_dc(impl_->memoryDC, hbmp);
}

void Application::teardown() {
  assert(impl_);

  delete impl_;
  impl_=nullptr;
}

void Application::run() {
  ShowWindow(impl_->mainWindow,SW_NORMAL);
  UpdateWindow(impl_->mainWindow);

  MSG msg;
  while (GetMessage(&msg,NULL,0,0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void Application::setOnFrameBeginEvent( onFrameBeginEvent_t onFrameBeginEvent ) {
  onFrameBeginEvent_=onFrameBeginEvent;
}

void Application::fireOnFrameBeginEvent() {
  HDC hdc=GetDC(impl_->mainWindow);
	BitBlt(hdc, 0, 0, width_, height_, impl_->memoryDC, 0, 0, SRCCOPY);
  ReleaseDC(impl_->mainWindow,hdc);
}

