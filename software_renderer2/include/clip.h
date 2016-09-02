//@date:2016.4.23
//@author:yangjie82@gmail.com
//@brief:clip triangle by rectangle
#pragma once
#include <vector>
#include "vec2.h"
class Triangle;
class Rect;

std::vector<Vec2> viewport_clip(const Triangle& triangle);