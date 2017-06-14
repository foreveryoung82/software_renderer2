//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:basic bitmap texture
#pragma once
#include "base.h"
#include "color.h"

class Texture {
 public:
  explicit Texture(const char* filename);
  virtual ~Texture();
  int width() const;
  int height() const;
  int line() const;
  int pitch() const;
  int bytesPerPixel() const;
  Color colorAt(int x,int y) const;
  //const u8* scanLine(int y) const;
  //const u8* data() const;

 private:
  Color*  pixels_;
  int     width_;
  int     height_;
  int     line_;
  int     pitch_;
  int     bytesPerPixel_;
};