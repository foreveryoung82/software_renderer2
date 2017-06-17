#pragma once
#include "texture.h"

inline Color Texture::colorAt(int x,int y) const {
  return pixels_[y*pitch_+x];
}