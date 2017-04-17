#include "rect.h"
using namespace std;

Rect Rect::make(f32 top, f32 left, f32 bottom, f32 right) {
  Rect rect;
  rect.top=top;
  rect.left=left;
  rect.bottom=bottom;
  rect.right=right;
  return rect;
}

Vec2 Rect::corner(u8 idx) const {
  return Vec2::make(m[idx],m[(idx+1)%4]);
}

