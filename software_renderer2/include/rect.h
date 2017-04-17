#pragma once
#include "base.h"
#include "vec2.h"

class Rect {
 public:
  static Rect make(f32 top, f32 left, f32 bottom, f32 right);
  union {
    struct {
      f32 top;
      f32 left;
      f32 bottom;
      f32 right;
    };
    f32 m[4];
  };
  f32& operator[](u8 idx) {return m[idx];}
  const f32& operator[](u8 idx) const {return m[idx];}
  Vec2 corner(u8 idx) const;
};