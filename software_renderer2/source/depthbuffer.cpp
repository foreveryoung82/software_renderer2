#include "depthbuffer.h"
#include <algorithm>

DepthBuffer::DepthBuffer(u32 width,u32 height)
 : width_(width)
 , height_(height)
 , buffer_(width*height,0.f) {
}

DepthBuffer::~DepthBuffer() {
}

f32 DepthBuffer::readAt(u32 x,u32 y) const {
  return buffer_[x+y*width_];
}

void DepthBuffer::writeAt(u32 x,u32 y,f32 z) {
  buffer_[x+y*width_]=z;
}

void DepthBuffer::clear() {
  std::fill(buffer_.begin(),buffer_.end(),0.f);
}