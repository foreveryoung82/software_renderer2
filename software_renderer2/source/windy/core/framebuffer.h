//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:framebuffer
#pragma once
#include "windy/base/basetype.h"

namespace windy {
class FrameBuffer {
 public:
  FrameBuffer(u32* raw_pixels,u32 width,u32 height,u32 stride);
  virtual ~FrameBuffer();
  int width() const {return width_;}
  int height() const {return height_;}
  inline void setPixel(int x,int y,u32 color) {rawPixels_[x+y*stride_/4]=color;}
  void clear(u32 color);

 private:
  u32* rawPixels_;
  u32  width_;
  u32  height_;
  u32  stride_;
};
}