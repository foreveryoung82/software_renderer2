#include "vec3.h"
#include <cmath>

const Vec3 Vec3::kZero=Vec3::make(0,0,0);
const Vec3 Vec3::kUnitX=Vec3::make(1,0,0);
const Vec3 Vec3::kUnitY=Vec3::make(0,1,0);
const Vec3 Vec3::kUnitZ=Vec3::make(0,0,1);

Vec3 Vec3::make(f32 x,f32 y,f32 z) {
  Vec3 ret;
  ret.x=x;
  ret.y=y;
  ret.z=z;
  return ret;  
}

bool Vec3::operator==(Vec3 const& rhs) const {
  return ((this->x==rhs.x) && (this->y==rhs.y) && (this->z==rhs.z));
}

f32 Vec3::dot(Vec3 const& rhs) const {
  return (x*rhs.x+y*rhs.y+z*rhs.z);
}

Vec3 Vec3::operator+(Vec3 const& rhs) const {
  return Vec3::make(x+rhs.x, y+rhs.y, z+rhs.z);
}

Vec3& Vec3::operator+=(Vec3 const& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  return *this;
}

Vec3 Vec3::operator-(Vec3 const& rhs) const {
  return Vec3::make(x-rhs.x, y-rhs.y, z-rhs.z);
}

Vec3& Vec3::operator-=(Vec3 const& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  return *this;  
}

Vec3 Vec3::operator-() const {
  return Vec3::make(-x, -y, -z);
}

Vec3 Vec3::operator*(f32 factor) const {
  return Vec3::make(factor*x, factor*y, factor*z);
}

Vec3& Vec3::operator*=(f32 factor) {
  x*=factor;
  y*=factor;
  z*=factor;
  return *this;
}

//f32 Vec3::length() const {
//  return std::sqrt(dot(*this));
//}
//
//f32 Vec3::lengthSquare() const {
//  return dot(*this);
//}

Vec3 operator*(f32 f, Vec3 const& lhs) {
  return lhs*f;
}

Vec3 operator*=(f32 f, Vec3& lhs) {
  return lhs*=f;
}