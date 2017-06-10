#include "vec3.h"
#include <cmath>
#include "vec4.h"

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

Vec3 Vec3::make(Vec4 const& v4) {
  Vec3 ret;
  ret.x=v4.x;
  ret.y=v4.y;
  ret.z=v4.z;
  return ret;
}

const f32* Vec3::begin() const {
  return &m[0];
}

f32* Vec3::begin() {
  return const_cast<f32*>(const_cast<const Vec3*>(this)->begin());  
}

const f32* Vec3::end() const {
  const int num=3;
  return &m[0]+num;
}

f32* Vec3::end() {
  return const_cast<f32*>(const_cast<const Vec3*>(this)->end());
}

bool Vec3::operator==(Vec3 const& rhs) const {
  return ((this->x==rhs.x) && (this->y==rhs.y) && (this->z==rhs.z));
}

f32 Vec3::dot(Vec3 const& rhs) const {
  return (x*rhs.x+y*rhs.y+z*rhs.z);
}

Vec3 Vec3::cross(Vec3 const& rhs) const {
  return Vec3::make(y*rhs.z-z*rhs.y,z*rhs.x-x*rhs.z,x*rhs.y-y*rhs.x);
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

f32 Vec3::length() const {
  return std::sqrt(dot(*this));
}

f32 Vec3::lengthSquare() const {
  return dot(*this);
}

Vec3 Vec3::normalized() const {
  return (1.f/length()) * *this;
}

Vec3 operator*(f32 f, Vec3 const& lhs) {
  return lhs*f;
}

Vec3 operator*=(f32 f, Vec3& lhs) {
  return lhs*=f;
}