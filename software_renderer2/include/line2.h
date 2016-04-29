//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for line 2d
#pragma once
#include <cstdint>
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
  Vec2 const& operator[](std::uint8_t idx) const {return m[idx];}
  Vec2& operator[](std::uint8_t idx) {return m[idx];};
  Vec2 normal() const;
};