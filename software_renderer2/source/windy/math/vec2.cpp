#include "windy/math/vec2.h"
#include <cmath>
#include "windy/math/vec3.h"
#include "windy/math/vec4.h"

namespace windy {
const Vec2 Vec2::kZero=Vec2::make(0,0);
const Vec2 Vec2::kUnitX=Vec2::make(1,0);
const Vec2 Vec2::kUnitY=Vec2::make(0,1);

Vec2 Vec2::make(f32 x,f32 y) {
  Vec2 ret;
  ret.x=x;
  ret.y=y;
  return ret;  
}

Vec2 Vec2::make(const Vec3& v) {
  return make(v.x,v.y);
}

Vec2 Vec2::make(const Vec4& v) {
  return make(v.x,v.y);
}

const f32* Vec2::begin() const {
  return &m[0];
}

f32* Vec2::begin() {
  return const_cast<f32*>(const_cast<const Vec2*>(this)->begin());  
}

const f32* Vec2::end() const {
  const int num=2;
  return &m[0]+num;
}

f32* Vec2::end() {
  return const_cast<f32*>(const_cast<const Vec2*>(this)->end());
}

bool Vec2::operator==(Vec2 const& rhs) const {
  return ((this->x==rhs.x) && (this->y==rhs.y));
}

f32 Vec2::dot(Vec2 const& rhs) const {
  return (x*rhs.x+y*rhs.y);
}

Vec2 Vec2::operator+(Vec2 const& rhs) const {
  return Vec2::make(x+rhs.x, y+rhs.y);
}

Vec2& Vec2::operator+=(Vec2 const& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  return *this;
}

Vec2 Vec2::operator-(Vec2 const& rhs) const {
  return Vec2::make(x-rhs.x, y-rhs.y);
}

Vec2& Vec2::operator-=(Vec2 const& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  return *this;  
}

Vec2 Vec2::operator-() const {
  return Vec2::make(-x, -y);
}

Vec2 Vec2::operator*(f32 factor) const {
  return Vec2::make(factor*x, factor*y);
}

Vec2& Vec2::operator*=(f32 factor) {
  x*=factor;
  y*=factor;
  return *this;
}

f32 Vec2::length() const {
  return std::sqrt(dot(*this));
}

f32 Vec2::lengthSquare() const {
  return dot(*this);
}

Vec2 Vec2::normalized() const {
  return (1.f/length()) * *this;
}

Vec2 operator*(f32 f, Vec2 const& lhs) {
  return lhs*f;
}

Vec2 operator*=(f32 f, Vec2& lhs) {
  return lhs*=f;
}
}