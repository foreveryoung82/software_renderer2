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


