//@date:2016.4.23
//@author:yangjie82@gmail.com
//@brief:clip triangle by rectangle
#pragma once
#include <vector>
#include "vec2.h"
#include "intersectresult.h"
class Triangle;
class Rect;
std::vector<Vec2> clip(std::vector<IntersectResult> const& segments,
                       Triangle const& triangle,
                       Rect const& rect);
                       //std::vector<Vec2> const& rectPts);

std::vector<Vec2> viewport_clip(const Triangle& triangle);