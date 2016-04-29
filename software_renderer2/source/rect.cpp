#include "rect.h"
using namespace std;

Rect Rect::make(float top, float left, float bottom, float right) {
  Rect rect;
  rect.top=top;
  rect.left=left;
  rect.bottom=bottom;
  rect.right=right;
  return rect;
}

Vec2 Rect::corner(std::uint8_t idx) const {
  return Vec2::make(m[idx],m[(idx+1)%4]);
}

