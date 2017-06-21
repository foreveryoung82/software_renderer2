//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:basic texture sampler
#pragma once
#include "base.h"
#include "color.h"

class Texture;
class Sampler {
 public:
  explicit Sampler(const Texture& tex);
  Color operator()(f32 u,f32 v) const;
  Color operator()(f32 u,f32 v,u32 mipmap_level) const;

 private:
  const Texture* texture_;
};