//@date:2017.6.23
//@author:51790592@qq.com
//@brief:simple window interface
#pragma once
#include "windy/base/basetype.h"

namespace windy {
class IMainWindow {
 public:
  virtual void show()=0;
  virtual u32 width() const=0;
  virtual u32 height() const=0;
};
}
