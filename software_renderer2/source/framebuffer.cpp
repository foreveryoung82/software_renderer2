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
  for (int h=0;h<height_;++h) {
    std::fill_n(&pixels_[h*stride_/4], width_, color);
  }
}


