#pragma once
#include "rasterizer.h"
#include <cassert>
#include "framebuffer.h"

inline void Rasterizer::setPixelAt( int x, int y, u32 color ) {
  assert(x<width_ && x>=0);
  assert(y<height_ && y>=0);

  framebuffer_->setPixel(x,y,color);
}