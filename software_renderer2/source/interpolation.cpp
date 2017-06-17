#include "interpolation.h"

// r=a+(b-a)*t
std::valarray<f32> lerp(
  std::valarray<f32> const& a,
  std::valarray<f32> const& b,
  f32 t) {
    std::valarray<f32> r;
    lerp(a,b,t,r);
    return r;
}

std::valarray<f32>& lerp(
  std::valarray<f32> const& a,
  std::valarray<f32> const& b,
  f32 t,
  std::valarray<f32>& r) {
  r=b;
  r-=a;
  r*=t;
  r+=a;
  return r;
}
