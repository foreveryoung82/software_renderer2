#include "framebuffer.h"
#include "framebuffer.inl"
#include <algorithm>

Framebuffer::Framebuffer( void* bytes,int width,int height,int stride )
 : pixels_(reinterpret_cast<unsigned int*>(bytes))
 , width_(width)
 , height_(height)
 , stride_(stride) {
}

Framebuffer::~Framebuffer() {
}

void Framebuffer::clear(unsigned int color) {
  std::fill_n(pixels_, height_*stride_/4, color);
}


