#include "framebuffer.h"

Framebuffer::Framebuffer( void* bytes,int width,int height,int stride )
 : bytes_(reinterpret_cast<unsigned int*>(bytes))
 , width_(width)
 , height_(height)
 , stride_(stride) {
}

Framebuffer::~Framebuffer() {
}

void Framebuffer::setPixel( int x,int y,unsigned int color ) {
  bytes_[x+y*stride_/4]=color;
}

void Framebuffer::clear(unsigned int color) {
  for (int h=0;h<height_;++h) {
    for (int c=0;c<width_;++c) {
      setPixel(c,h,color);
    }
  }
}


