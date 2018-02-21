//@date:2018.2.21
//@author:yangjie82@gmail.com
//@brief:simple rgba color
#pragma once
#include "windy/base/basetype.h"
#include "windy/math/common.h"

namespace windy {
struct Color {
  u8 Blue;
  u8 Green;
  u8 Red;
  u8 Alpha;
  u32 Value() const {return *reinterpret_cast<const u32*>(this);}
};

template<>
inline Color lerp<Color>(Color const& a,Color const& b,f32 t) {
  Color c;
  c.Alpha = static_cast<u32>(lerp<f32>(a.Alpha,b.Alpha,t));
  c.Red   = static_cast<u32>(lerp<f32>(a.Red,b.Red,t));
  c.Green = static_cast<u32>(lerp<f32>(a.Green,b.Green,t));
  c.Blue  = static_cast<u32>(lerp<f32>(a.Blue,b.Blue,t));
  return c;
}
}