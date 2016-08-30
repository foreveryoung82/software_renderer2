//@date:2016.8.30
//@author:yangjie82@gmail.com
//@brief:divide triangle into at most 2 trapezoids
#pragma once
#include <vector>
#include "vec2.h"
#include "line2.h"

class Triangle;
class Trapezoid {
 public:
  Line2 l; // left edge
  Line2 r; // right edge
  float t; // top y
  float b; // bottom y
};

int divide_into_trapezoids(const Triangle& triangle, Trapezoid* trapezoids);