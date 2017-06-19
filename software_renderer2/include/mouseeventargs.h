//@date:2017.6.19
//@author:yangjie82@gmail.com
//@brief:mouse event arguments
#include "base.h"

struct MouseEventArgs {
  enum class Event {
    LeftButtonDown,
    LeftButtonUp,
    RightButtonDown,
    RightButtonUp,
    Move,
  };
  u32   X;
  u32   Y;
  Event Type;
};