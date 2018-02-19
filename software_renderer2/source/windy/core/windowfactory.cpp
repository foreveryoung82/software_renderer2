#include "windy/core/windowfactory.h"
#include "windy/core/mainwindowwin32.h"

namespace windy {
IMainWindow* WindowFactory::createMainWindow(u32 width,u32 height) {
  return new MainWindowWin32(width,height);
}

void WindowFactory::destroyMainWindow(IMainWindow* window) {
  delete window;
}
}