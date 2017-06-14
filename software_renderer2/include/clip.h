//@date:2016.4.23
//@author:yangjie82@gmail.com
//@brief:clip triangle by rectangle
#pragma once
#include <vector>
#include <valarray>
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
std::vector<Vec4> homogeneous_clip_view_frustum(Vec4 const& v0,
                                                Vec4 const& v1,
                                                Vec4 const& v2);

int homogeneous_clip_infinitesimal_w(
  int idx0,
  int idx1,
  int idx2,
  const std::vector<Vec4>&                inXYZW,
  const std::vector<std::valarray<f32>*>& inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>*>&       outUV);

int homogeneous_clip_view_frustum(
  int idx0,
  int idx1,
  int idx2,
  const std::vector<Vec4>&                inXYZW,
  const std::vector<std::valarray<f32>*>& inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>*>&       outUV);
