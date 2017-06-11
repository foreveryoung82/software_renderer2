//@date:2016.4.23
//@author:yangjie82@gmail.com
//@brief:clip triangle by rectangle
#pragma once
#include <vector>
#include "vec2.h"
#include "vec4.h"
class Triangle;
class Triangle3D;

std::vector<Vec2> viewport_clip(const Triangle& triangle);
std::vector<Vec4> homogeneous_clip(Vec4 const& a,Vec4 const& c);
//std::vector<Triangle3D> homogenous_clip(Vec4 const& v0,
//                                        Vec4 const& v1,
//                                        Vec4 const& v2);
std::vector<Vec4> homogeneous_clip(Vec4 const& v0,
                                  Vec4 const& v1,
                                  Vec4 const& v2);
std::vector<Vec4> homogeneous_clip_infinitesimal_w(Vec4 const& v0,
                                                   Vec4 const& v1,
                                                   Vec4 const& v2);