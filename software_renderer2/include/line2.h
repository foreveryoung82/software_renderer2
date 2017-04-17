//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for line 2d
#pragma once
#include "base.h"
#include "vec2.h"

class Line2 {
 public:
  static Line2 make(Vec2 const& aS, Vec2 const& aT);
  union {
    struct {
      Vec2 s;
      Vec2 t;
    };
    Vec2 m[2];
  };
  Vec2 const& operator[](u8 idx) const {return m[idx];}
  Vec2& operator[](u8 idx) {return m[idx];};
  Vec2 normal() const;
};