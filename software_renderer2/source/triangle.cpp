#include "triangle.h"
#include "line2.h"

Triangle Triangle::make(Vec2 const& p0, Vec2 const& p1, Vec2 const& p2) {
  Triangle ret;
  ret.p0=p0;
  ret.p1=p1;
  ret.p2=p2;
  return ret;
}