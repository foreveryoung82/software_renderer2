#pragma once
#include <cstdint>
#include "vec2.h"

class Rect {
 public:
  static Rect make(float top, float left, float bottom, float right);
  union {
    struct {
      float top;
      float left;
      float bottom;
      float right;
    };
    float m[4];
  };
  float& operator[](std::uint8_t idx) {return m[idx];}
  const float& operator[](std::uint8_t idx) const {return m[idx];}
  Vec2 corner(std::uint8_t idx) const;
};