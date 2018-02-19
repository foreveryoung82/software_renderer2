#include "windy/core/mainwindowwin32.h"

namespace windy {
MainWindowWin32* MainWindowWin32::s_singleton=nullptr;

MainWindowWin32::MainWindowWin32(u32 width,u32 height)
 : windowClassName_(TEXT("windy engine windows class"))
 , width_(width)
 , height_(height)
 , nativeHandle_(0)
 , wndProcFunc_()
{
  WNDCLASS wnd_class;
  wnd_class.style = CS_HREDRAW | CS_VREDRAW;
  wnd_class.lpfnWndProc = wndProc_;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0;
  wnd_class.hInstance = NULL;
  wnd_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);;
  wnd_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wnd_class.lpszMenuName = NULL;
  wnd_class.lpszClassName = windowClassName_;  
  if (!RegisterClass(&wnd_class)) {
    MessageBox(NULL,
      TEXT("Register window class failed!"),
      TEXT("Error"),
      MB_ICONERROR);
  }

  HWND hwnd = CreateWindow(
    windowClassName_,
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
  RECT rect = { 0,0,static_cast<LONG>(width),static_cast<LONG>(height) };
  AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), FALSE);
  int win_width = rect.right - rect.left;
  int win_height = rect.bottom - rect.top;
  SetWindowPos(hwnd,
    NULL,
    0,
    0,
    win_width,
    win_height,
    (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
  nativeHandle_=hwnd;
  width_  = width;
  height_ = height;  

  s_singleton=this;
}
  
MainWindowWin32::~MainWindowWin32() {
  s_singleton=nullptr;
}

void MainWindowWin32::show() {
  ShowWindow(nativeHandle_, SW_NORMAL);
  UpdateWindow(nativeHandle_);
}

LRESULT MainWindowWin32::wndProc_(HWND hwnd,
                                  UINT message,
                                  WPARAM wParam,
                                  LPARAM lParam) {
  if (s_singleton && s_singleton->wndProcFunc_) {
    auto& func=s_singleton->wndProcFunc_;
    if (func)
        func(hwnd,message,wParam,lParam);
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}
}