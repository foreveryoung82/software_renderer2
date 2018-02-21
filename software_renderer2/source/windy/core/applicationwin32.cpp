#include "windy/core/applicationWin32.h"
#include <cassert>
#include "windy/core/frameworkconfig.h"
#include "windy/core/iclient.h"
#include "windy/core/imainwindow.h"
#include "windy/core/mainwindowwin32.h"
#include "windy/core/renderdevice.h"
#include "windy/core/windowfactory.h"
#include "windy/service/servicetime.h"

//#include <windowsx.h>
#include <wrl/client.h>

namespace windy {
static ApplicationWin32* s_instance=nullptr;

ApplicationWin32::ApplicationWin32() 
 : mainWindow_(nullptr)
 , renderDevice_(nullptr)
 , client_(nullptr)
 , finalizerStack_()
{
  assert(nullptr==s_instance);

  s_instance=this;
}

ApplicationWin32::~ApplicationWin32() {

  while ( !finalizerStack_.empty() ) {
    auto& finalizer=finalizerStack_.top();
    finalizer();
    finalizerStack_.pop();
  }

  assert(nullptr!=s_instance);

  s_instance=nullptr;
}

IMainWindow& ApplicationWin32::mainWindow() const {
  return *mainWindow_;
}

void ApplicationWin32::run(IClient& client) {
  startAllServices_();
  
  client_=&client;
  const FrameworkConfig& config=client.config();
  mainWindow_=WindowFactory::createMainWindow(config.width,config.height);
  static_cast<MainWindowWin32*>(mainWindow_)->setWndProc(
        [this](HWND hwnd,
               UINT message,
               WPARAM wParam,
               LPARAM lParam){
    wndProc_(hwnd,message,wParam,lParam);
  });

  //renderDevice_=new RenderDevice(*mainWindow_,640,480);
  renderDevice_=new RenderDevice(*mainWindow_,3,3);
  mainWindow_->show();

  ServiceTime& st=ServiceTime::instance();
  st.startTimer(ServiceTime::TimerID::Client);

  bool  shouldGoOn=true;
  MSG   msg;
  while (shouldGoOn) {
    while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  
      shouldGoOn &= (WM_QUIT!=msg.message);
    }
  }

  delete renderDevice_;
  renderDevice_=nullptr;

  WindowFactory::destroyMainWindow(mainWindow_);
  mainWindow_=nullptr;
}

void ApplicationWin32::registerFinalizer(finalizer_t finalizer) {
}

void ApplicationWin32::startAllServices_() {
  startService_<ServiceTime>();
}

void ApplicationWin32::wndProc_(HWND hwnd,
                                UINT message,
                                WPARAM wParam,
                                LPARAM lParam) {

  switch(message) {
    case WM_CREATE:
      break;
    case WM_PAINT: {
      // to avoid repeatedly receiving WM_PAINT message
      PAINTSTRUCT ps;
      BeginPaint(hwnd,&ps);
      if (renderDevice_)
        renderDevice_->present();
      EndPaint(hwnd,&ps);
      break;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
    }
  }
}

IFramework& GetFrameworkInstance() {
  return *s_instance;
}
}