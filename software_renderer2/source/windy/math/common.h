//@date:2017.8.8
//@author:yangjie82@gmail.com
//@brief:math common constant and function
#pragma once
//#include <valarray>
#include "windy/base/basetype.h"

namespace windy {
constexpr f32 kPi=3.141592653589793f;

// r=a+(b-a)*t
template<class _Ty>
_Ty lerp(_Ty const& a,_Ty const& b,f32 t) {
  return (a+(b-a)*t);
}
}