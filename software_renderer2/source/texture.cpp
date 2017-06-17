#include "texture.h"
#include "texture.inl"
#include <sstream>
#include <stdexcept>
#pragma warning(push)
#pragma warning(disable:4819)
#include <freeimage/FreeImage.h>
#pragma warning(pop)

Texture::Texture(const char* filename) {
  FREE_IMAGE_FORMAT format=FreeImage_GetFileType(filename,0);

  if (FIF_PNG != format)
    throw std::exception("Unaccepted texture file format!");

  FIBITMAP* bmp=FreeImage_Load(FIF_PNG,filename,0);
  if (!bmp) {
    std::stringstream ss;
    ss<<"Texture file: \""<<filename<<"\" open failed!";
    throw std::exception(ss.str().c_str());
  }

  int bpp=FreeImage_GetBPP(bmp);
  if ((24!=bpp) && (32!=bpp)) {
    FreeImage_Unload(bmp);
    std::stringstream ss;
    ss<<"Texture file: \""<<filename<<"\" bpp is not accepted!";
    throw std::exception(ss.str().c_str());
  }

  width_ = FreeImage_GetWidth(bmp);
  height_= FreeImage_GetWidth(bmp);
  line_  = FreeImage_GetLine(bmp);
  pitch_ = FreeImage_GetPitch(bmp);
  bytesPerPixel_ = bpp;
  pixels_ = new Color[height_*pitch_];
  RGBQUAD quad;
  for(int y=0;y<height_;++y) {
    for(int x=0;x<width_;++x) {
      Color& color=pixels_[y*pitch_+x];
      FreeImage_GetPixelColor(bmp,x,y,&quad);
      color.Red   = quad.rgbRed;
      color.Green = quad.rgbGreen;
      color.Blue  = quad.rgbBlue;
    }
  }

  FreeImage_Unload(bmp);
}

Texture::~Texture() {
  delete [] pixels_;
}

int Texture::width() const {
  return width_;
}

int Texture::height() const {
  return height_;
}

int Texture::line() const {
  return line_;
}

int Texture::pitch() const {
  return pitch_;
}

int Texture::bytesPerPixel() const {
  return bytesPerPixel_;
}
