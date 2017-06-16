//@date:2016.8.30
//@author:yangjie82@gmail.com
//@brief:divide triangle into at most 2 trapezoids
#pragma once
#include <vector>
#include "base.h"
#include "line2.h"
#include "vec2.h"
class PrimitiveStream;
class Triangle;

class Trapezoid {
 public:
  Line2 l; // left edge
  Line2 r; // right edge
  f32 t; // top y
  f32 b; // bottom y
};

struct IndexedTrapezoid {
  u32 l[2]; // left edge
  u32 r[2]; // right edge
  f32 t; // top y
  f32 b; // bottom y
};

int divide_into_trapezoids(const Triangle& triangle, Trapezoid* trapezoids);

int divide_into_trapezoids(u32                    primitiveIndex,
                           const PrimitiveStream& stream,
                           IndexedTrapezoid*      trapezoids);