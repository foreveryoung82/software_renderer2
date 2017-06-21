//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:basic bitmap texture
#pragma once
#include <vector>
#include "base.h"
#include "color.h"

class Texture {
 public:
  explicit Texture(const char* filename);
  virtual ~Texture();
  int width() const;
  int width(u32 mipmap_level) const;
  int height() const;
  int height(u32 mipmap_level) const;
  int line() const;
  //int pitch() const;
  int bytesPerPixel() const;
  inline Color colorAt(int x,int y) const;
  inline Color colorAt(int x,int y,u32 mipmap_level) const;
  u32 generateMipmapChain();
  u32 maxMipmapLevel() const;
  //const u8* scanLine(int y) const;
  //const u8* data() const;

 private:
  typedef std::vector<Color>      Surface_t;
  typedef std::vector<Surface_t>  Chain_t;
  //typedef std::vector<u32>        Pitches_t;
  Chain_t   chain_;
  //std::vector<u32> pitches_;
  std::vector<u32> widthes_;
  std::vector<u32> heights_;
  int width_;
  int height_;
  int line_;
  //int pitch_;
  int bytesPerPixel_;
  
  static Surface_t generateCoarserMipmap(Surface_t& deteil,
                                         u32* width,
                                         u32* height);
};