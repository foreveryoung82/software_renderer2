#include "Line2.h"
#include <cmath>
#include <limits>

using namespace std;

Line2 Line2::make(Vec2 const& s, Vec2 const& t) {
  Line2 ret;
  ret.s=s;
  ret.t=t;
  return ret;
}

Vec2 Line2::normal() const {
  Vec2 d=t-s;
  return Vec2::make(-d.y,d.x);
}