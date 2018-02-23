//@date:2018.1.30
//@author:51790592@qq.com
//@brief:platform specific application base class
#pragma once
#include <stack>
#include "windy/core/iframework.h"
#include "windy/core/imainwindow.h"

#include <wrl/client.h>

namespace windy {
class IClient;
class IFramework;
class RenderDevice;
}

namespace windy {
class ApplicationWin32:public IFramework {
 public:
  ApplicationWin32();
  virtual ~ApplicationWin32();
  virtual IMainWindow& mainWindow() const override;
  virtual void run(IClient& client) override;
  virtual void registerFinalizer(finalizer_t finalizer) override;

private:
  IMainWindow*  mainWindow_;
  RenderDevice* renderDevice_;
  IClient*      client_;
  std::stack<finalizer_t> finalizerStack_;

  void startAllServices_();
  void fireFrameEvent_();
  void wndProc_(HWND hwnd,
               UINT message,
               WPARAM wParam,
               LPARAM lParam);

  template <class _Ty>
  void startService_() {
    _Ty::initialize();
    registerFinalizer(_Ty::finalize);
  }
};
}