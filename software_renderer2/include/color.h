//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:simple rgba color
#pragma once
#include "base.h"

struct Color {
  u8 Red;
  u8 Green;
  u8 Blue;
  u8 Alpha;
  u32 Value() const {return (((u32)Red)<<16)|(((u32)Green)<<8)|(((u32)Blue));}
};