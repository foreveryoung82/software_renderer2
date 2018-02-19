//@date:2018.1.31
//@author:51790592@qq.com
//@brief:window factory
#pragma once
#include "windy/base/basetype.h"
namespace windy {
class IMainWindow;
}

namespace windy {
class WindowFactory {
 public:
  static IMainWindow* createMainWindow(u32 width,u32 height);
  static void destroyMainWindow(IMainWindow* window);
};
}