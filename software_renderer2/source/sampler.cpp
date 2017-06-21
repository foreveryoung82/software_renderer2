#include "sampler.h"
#include <cmath>
#include <algorithm>
#include "texture.h"
#include "texture.inl"

namespace {
  inline f32 saturate(f32 v) {return std::min(std::max(0.f, v), 1.f);}
}

Sampler::Sampler(const Texture& tex)
 : texture_(&tex) {
}

Color Sampler::operator()(f32 u,f32 v) const {
  const int x=static_cast<int>(saturate(u)*(texture_->width()-1)+0.5f);
  const int y=static_cast<int>(saturate(v)*(texture_->height()-1)+0.5f);
  return texture_->colorAt(x,y);
}

Color Sampler::operator()(f32 u,f32 v,u32 mipmap_level) const {
  const int x=static_cast<int>(saturate(u)*(texture_->width(mipmap_level)-1)+0.5f);
  const int y=static_cast<int>(saturate(v)*(texture_->height(mipmap_level)-1)+0.5f);
  return texture_->colorAt(x,y,mipmap_level);
}