//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:framebuffer
#pragma once

class Framebuffer {
 public:
  Framebuffer(void* bytes,int width,int height,int stride);
  virtual ~Framebuffer();
  int width() const {return width_;}
  int height() const {return height_;}
  void setPixel(int x,int y,unsigned int color);
  void clear(unsigned int color);

 private:
  unsigned int* bytes_;
  int width_;
  int height_;
  int stride_;
};