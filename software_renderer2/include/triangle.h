//@date:2016.4.23
//@author:yangjie82@gmail.com
//@brief:triangle class
#pragma once
#include "base.h"
#include "vec2.h"

//逆时针方向顶点描述的三角形
class Triangle {
 public:
  static Triangle make(Vec2 const& p0, Vec2 const& p1, Vec2 const& p2);
  union {
    struct {
      Vec2 p0;
      Vec2 p1;
      Vec2 p2;
    };
    Vec2 m[3];
  };
  Vec2& operator[](u8 idx) {return m[idx];}
  const Vec2& operator[](u8 idx) const {return m[idx];}
  //Triangle scale(f32 scale_x, f32 scale_y) const;
};