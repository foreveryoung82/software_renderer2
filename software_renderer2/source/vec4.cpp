#include "vec4.h"
#include <cmath>
#include "vec3.h"

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

Vec4 Vec4::make(Vec3 const& v, f32 w) {
  Vec4 ret;
  ret.x=v.x;
  ret.y=v.y;
  ret.z=v.z;
  ret.w=w;
  return ret;    
}

Vec4 Vec4::computeShortestRotation(const Vec3& unitA,const Vec3& unitB) {
  Vec4 ret = Vec4::make(unitA.cross(unitB),unitA.dot(unitB));
  ret.w+=1;
  // [cos(a)+1, sin(a)v] = 2cos(a/2)[cos(a/2), sin(a/2)]
  return ret.normalized(); 
}

const f32* Vec4::begin() const {
  return &m[0];
}

f32* Vec4::begin() {
  return const_cast<f32*>(const_cast<const Vec4*>(this)->begin());  
}

const f32* Vec4::end() const {
  const int num=4;
  return &m[0]+num;
}

f32* Vec4::end() {
  return const_cast<f32*>(const_cast<const Vec4*>(this)->end());
}

bool Vec4::operator==(Vec4 const& rhs) const {
  return ((this->x==rhs.x) &&
          (this->y==rhs.y) &&
          (this->z==rhs.z) &&
          (this->w==rhs.w));
}

f32 Vec4::dot(Vec4 const& rhs) const {
  return (x*rhs.x+y*rhs.y+z*rhs.z+w*rhs.w);
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

const Vec3& Vec4:: v() const {
  return *reinterpret_cast<const Vec3*>(this);
}

Vec3& Vec4::v() {
  return *reinterpret_cast<Vec3*>(this);
}

f32 Vec4::length() const {
  return std::sqrt(dot(*this));
}

f32 Vec4::lengthSquare() const {
  return dot(*this);
}

Vec4 Vec4::normalized() const {
  return (1.f/length()) * *this;
}

Vec4 Vec4::conjugate() const {
  return Vec4::make(-x,-y,-z,w);
}

Vec4 Vec4::inverse() const {
  return conjugate()*(1.f/length());
}

Vec4 Vec4::quaternionMultiply(const Vec4& q) const {
  const f32  rw = w*q.w-v().dot(q.v());
  const Vec3 rv = w*q.v()+v()*q.w+v().cross(q.v());
  return Vec4::make(rv, rw);
}

Vec4 operator*(f32 f, Vec4 const& lhs) {
  return lhs*f;
}

Vec4 operator*=(f32 f, Vec4& lhs) {
  return lhs*=f;
}