//@date:2017.6.19
//@author:yangjie82@gmail.com
//@brief:depth buffer
#pragma once
#include <vector>
#include "base.h"

class DepthBuffer {
 public:
  explicit DepthBuffer(u32 width,u32 height);
  ~DepthBuffer();
  f32 readAt(u32 x,u32 y) const;
  void writeAt(u32 x,u32 y,f32 z);
  void clear();

 private:
  u32 width_;
  u32 height_;
  std::vector<f32> buffer_;  
};