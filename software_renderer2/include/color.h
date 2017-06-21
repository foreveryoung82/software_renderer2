//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:simple rgba color
#pragma once
#include "base.h"
#include "interpolation.h"

struct Color {
  u8 Blue;
  u8 Green;
  u8 Red;
  u8 Alpha;
  //u32 Value() const {return (((u32)Red)<<16)|(((u32)Green)<<8)|(((u32)Blue));}
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