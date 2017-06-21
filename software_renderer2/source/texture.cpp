#include "texture.h"
#include "texture.inl"
#include <sstream>
#include <stdexcept>
#pragma warning(push)
#pragma warning(disable:4819)
#include <freeimage/FreeImage.h>
#pragma warning(pop)
#include "bithack.h"
#include "bithack.inl"
#include "color.h"

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
  // we don't support non-power-of-2 textures
  const bool is_pot=(BitHack::isPowerOf2(width_)&&BitHack::isPowerOf2(height_));
  const bool is_square=(width_==height_);
  if ((!is_pot) || (!is_square)) {
    FreeImage_Unload(bmp);
    std::stringstream ss;
    ss<<"Texture file: \""<<filename<<"\" is not square power-of-2 !";
    throw std::exception(ss.str().c_str());    
  }
  line_  = FreeImage_GetLine(bmp);
  bytesPerPixel_ = bpp/8;
  // remark(yangjie82@gmail.com):we store pixels in compacted buffer instead of
  // with some extra empty space in each line
  //pitch_ = FreeImage_GetPitch(bmp);
  //pitch_=line_/bytesPerPixel_; 
  chain_.emplace_back(height_*width_);
  //pitches_.push_back(pitch_);
  widthes_.push_back(width_);
  heights_.push_back(height_);
  RGBQUAD quad;
  for(int y=0;y<height_;++y) {
    for(int x=0;x<width_;++x) {
      Color& color=chain_[0][y*width_+x];
      FreeImage_GetPixelColor(bmp,x,y,&quad);
      color.Red   = quad.rgbRed;
      color.Green = quad.rgbGreen;
      color.Blue  = quad.rgbBlue;
    }
  }

  FreeImage_Unload(bmp);
}

Texture::~Texture() {
}

int Texture::width() const {
  return width_;
}

int Texture::width(u32 mipmap_level) const {
  return widthes_[mipmap_level];
}

int Texture::height() const {
  return height_;
}

int Texture::height(u32 mipmap_level) const {
  return heights_[mipmap_level];
}

int Texture::line() const {
  return line_;
}

//int Texture::pitch() const {
//  return pitch_;
//}

int Texture::bytesPerPixel() const {
  return bytesPerPixel_;
}

u32 Texture::generateMipmapChain() {
  u32 w  = width_;
  u32 h = height_;
  Surface_t* deteil_lod=&chain_[0];
  while (w>1) { // require square and pot texture
    chain_.push_back(generateCoarserMipmap(*deteil_lod,&w,&h));
    //pitches_.push_back(w);
    widthes_.push_back(w);
    heights_.push_back(h);
    deteil_lod=&chain_.back();
  }
  return maxMipmapLevel();
}

u32 Texture::maxMipmapLevel() const {
  return chain_.size()-1;
}

Texture::Surface_t Texture::generateCoarserMipmap(Surface_t& deteil,
                                                  u32* width,
                                                  u32* height) {
    const u32 old_w=*width;
    const u32 w=*width/2;
    const u32 h=*height/2;
    Surface_t coarse(w*h);

    for(u32 y=0;y<h;++y) {
      for(u32 x=0;x<w;++x) {
        const u32 xy=x*2+y*2*old_w; // (2x,2y) with width=2*w
        Color c0=lerp<Color>(deteil[xy],deteil[xy+1],0.5f);
        Color c1=lerp<Color>(deteil[xy+old_w],deteil[xy+old_w+1],0.5f);
        coarse[x+y*w]=lerp<Color>(c0,c1,0.5f);
      }
    }
    *width=w;
    *height=h;
    return coarse;
}
