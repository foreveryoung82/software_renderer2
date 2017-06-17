#pragma once
#include "framebuffer.h"

inline void Framebuffer::setPixel( int x,int y,u32 color ) {
  pixels_[x+y*stride_/4]=color;
}