//@date:2018.1.31
//@author:51790592@qq.com
//@brief:simple win32 window
#pragma once
#include <functional>
#include "windy/base/basetype.h"
#include "windy/core/imainwindow.h"

#include <wrl/client.h>

namespace windy {
class MainWindowWin32:public IMainWindow {
 public:
  typedef std::function<void(HWND hwnd,
                             UINT message,
                             WPARAM wParam,
                             LPARAM lParam)>
          wndProc_t;

  MainWindowWin32(u32 width,u32 height);
  virtual ~MainWindowWin32();
  virtual void show() override;

  void setWndProc(wndProc_t wnd_proc_func) {wndProcFunc_=wnd_proc_func;}

 private:
  static MainWindowWin32* s_singleton;

  TCHAR*    windowClassName_;
  wndProc_t wndProcFunc_;


  u32       width_;
  u32       height_;
  HWND      nativeHandle_;

  static LRESULT CALLBACK wndProc_(HWND hwnd,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam);
};
}