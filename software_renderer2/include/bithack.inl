#pragma once
#include "bithack.h"

inline bool BitHack::isPowerOf2(u32 n) {
  return ((n & (n-1))==0);
}