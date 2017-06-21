#pragma once
#include "texture.h"

inline Color Texture::colorAt(int x,int y) const {
  return chain_[0][y*width_+x];
}

inline Color Texture::colorAt(int x,int y,u32 mipmap_level) const {
  return chain_[mipmap_level][y*widthes_[mipmap_level]+x];
}
