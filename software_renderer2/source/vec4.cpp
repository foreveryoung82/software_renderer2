#include "vec4.h"
#include <cmath>

const Vec4 Vec4::kZero=Vec4::make(0,0,0,0);
const Vec4 Vec4::kUnitX=Vec4::make(1,0,0,0);
const Vec4 Vec4::kUnitY=Vec4::make(0,1,0,0);
const Vec4 Vec4::kUnitZ=Vec4::make(0,0,1,0);
const Vec4 Vec4::kUnitW=Vec4::make(0,0,0,1);

Vec4 Vec4::make(f32 x,f32 y,f32 z,f32 w) {
  Vec4 ret;
  ret.x=x;
  ret.y=y;
  ret.z=z;
  ret.w=w;
  return ret;  
}

bool Vec4::operator==(Vec4 const& rhs) const {
  return ((this->x==rhs.x) &&
          (this->y==rhs.y) &&
          (this->z==rhs.z) &&
          (this->w==rhs.w));
}

Vec4 Vec4::operator+(Vec4 const& rhs) const {
  return Vec4::make(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

Vec4& Vec4::operator+=(Vec4 const& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  w+=rhs.w;
  return *this;
}

Vec4 Vec4::operator-(Vec4 const& rhs) const {
  return Vec4::make(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

Vec4& Vec4::operator-=(Vec4 const& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  w-=rhs.w;
  return *this;  
}

Vec4 Vec4::operator-() const {
  return Vec4::make(-x, -y, -z, -w);
}

Vec4 Vec4::operator*(f32 factor) const {
  return Vec4::make(factor*x, factor*y, factor*z, factor*w);
}

Vec4& Vec4::operator*=(f32 factor) {
  x*=factor;
  y*=factor;
  z*=factor;
  w*=factor;
  return *this;
}

//f32 Vec4::length() const {
//  return std::sqrt(dot(*this));
//}
//
//f32 Vec4::lengthSquare() const {
//  return dot(*this);
//}

Vec4 operator*(f32 f, Vec4 const& lhs) {
  return lhs*f;
}

Vec4 operator*=(f32 f, Vec4& lhs) {
  return lhs*=f;
}