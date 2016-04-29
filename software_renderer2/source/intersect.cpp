#include "intersect.h"
#include <cassert>
#include <cstdint>
#include <algorithm>
#include "rect.h"
#include "triangle.h"
#include "line2.h"
#include "partition.h"
using namespace std;

namespace {
enum Outcode: uint8_t {
  Left=0x01,
  Right=0x01<<1,
  Bottom=0x01<<2,
  Top=0x01<<3,
};

uint8_t outcode(Vec2 const& point, Rect const& rect) {
  uint8_t result=0;
  if (point.x<rect.left)
    result|=Outcode::Left;
  else if (point.x>rect.right)
    result|=Outcode::Right;
  if (point.y<rect.bottom)
    result|=Outcode::Bottom;
  else if (point.y>rect.top)
    result|=Outcode::Top;
  return result;
}

static const uint8_t s_bitOrderToBoundIdx[4] = {
  1,3,2,0
};

float bit_order_to_bound(Rect const& rect, uint8_t bitOrder) {
  return rect[s_bitOrderToBoundIdx[bitOrder]];
}
}

bool intersect(Triangle const& triangle, Vec2 const& point) {
  for (int i=0;i<3;++i) {
    Line2 edge=Line2::make(triangle[i],triangle[(i+1)%3]);
    if (PartitionResult::kRight==partition(edge,point))
      return false;
  }
  return true;
}

bool intersect(Vec2 const& point, Triangle const& triangle) {
  return intersect(triangle,point);
}

bool intersect(Line2 const& line, Rect const& rect, IntersectResult& result) {
  return intersect(rect, line, result);
}

bool intersect(Rect const& rect, Line2 const& line, IntersectResult& result) {
  const Vec2& s=line.s;
  const Vec2& t=line.t;
  const uint8_t os=outcode(s, rect);  // outcode of s
  const uint8_t ot=outcode(t, rect);  // outcode of t
  if (os&ot)
    return result.isIntersected=false;
  uint8_t code=0x01;
  float enter=0;
  float exit=1;
  for (int i=0;i<2;++i) {
    float cs=s[i];  // coordinate i of s
    float ct=t[i];  // coordinate i of t
    uint8_t bitOrder=2*i;
    const float cd=ct-cs;
    float lambda=(bit_order_to_bound(rect,bitOrder)-cs)/cd;
    uint8_t idxBound=s_bitOrderToBoundIdx[bitOrder];
    if ((code&os) && (lambda>enter)) {
      result.rectBoundIdx[0]=idxBound;
      enter=lambda;
    }
    if ((code&ot) && (lambda<exit)) {
      result.rectBoundIdx[1]=idxBound;
      exit=lambda;
    }    
    code=code<<1;
    ++bitOrder;
    lambda=(bit_order_to_bound(rect,bitOrder)-cs)/cd;
    idxBound=s_bitOrderToBoundIdx[bitOrder];
    if ((code&os) && (lambda>enter)) {
      result.rectBoundIdx[0]=idxBound;
      enter=lambda;
    }
    if ((code&ot) && (lambda<exit)) {
      result.rectBoundIdx[1]=idxBound;
      exit=lambda;
    }
    code=code<<1; 
  }
  if (enter>exit) {
    result.isIntersected=false;
    return false;
  }
  const Vec2 delta=t-s;
  Line2& l=result.line;
  l.s=s+enter*delta;
  l.t=s+exit*delta;
  return result.isIntersected=true;
}

bool intersect(Rect const& rect, Triangle const& triangle, std::vector<IntersectResult>& result) {
  bool isIntersected=false;
  for (int i=0;i<3;++i) {
    const int j=(i+1)%3;
    Line2 edge=Line2::make(triangle[i], triangle[j]);
    IntersectResult ir;
    if (intersect(rect,edge,ir)) {
      result.push_back(ir);
      isIntersected=true;
    }
  }
  return isIntersected;
}