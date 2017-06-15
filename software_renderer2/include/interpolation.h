//@date:2017.6.15
//@author:yangjie82@gmail.com
//@brief:interpolation algorithm
#pragma once
#include <valarray>
#include "base.h"

template<class _Ty>
_Ty lerp(_Ty const& a,_Ty const& b,f32 t) {
  return (a+(b-a)*t);
}

// r=a+(b-a)*t
std::valarray<f32> lerp(
  std::valarray<f32> const& a,
  std::valarray<f32> const& b,
  f32 t) {
  std::valarray<f32> r=b;
  r-=a;
  r*=t;
  r+=a;
  return r;
}
