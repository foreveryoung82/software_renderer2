//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:framebuffer
#pragma once
#include "base.h"

class Framebuffer {
 public:
  Framebuffer(void* bytes,int width,int height,int stride);
  virtual ~Framebuffer();
  int width() const {return width_;}
  int height() const {return height_;}
  inline void setPixel(int x,int y,u32 color);
  void clear(unsigned int color);

 private:
  u32* pixels_;
  int  width_;
  int  height_;
  int  stride_;
};