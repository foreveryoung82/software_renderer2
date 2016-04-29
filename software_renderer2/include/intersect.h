//@date:2016.4.23
//@author:yangjie82@moonton.com
//@brief:ÓÃ¾ØÐÎ²Ã¼ôÏß¶Î
#pragma once
#include <vector>
#include "intersectresult.h"

class Triangle;
class Rect;
class Line2;
//triangle vs point
bool intersect(Triangle const& triangle, Vec2 const& point);
bool intersect(Vec2 const& point, Triangle const& triangle);
//rect vs line
bool intersect(Rect const& rect, Line2 const& line, IntersectResult& result);
bool intersect(Line2 const& line, Rect const& rect, IntersectResult& result);
//rect vs triangle
bool intersect(Rect const& rect, Triangle const& triangle, std::vector<IntersectResult>& result);