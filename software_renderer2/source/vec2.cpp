#include "vec2.h"
#include <cmath>

const Vec2 Vec2::kZero=Vec2::make(0,0);
const Vec2 Vec2::kUnitX=Vec2::make(1,0);
const Vec2 Vec2::kUnitY=Vec2::make(0,1);

Vec2 Vec2::make(float x,float y) {
  Vec2 ret;
  ret.x=x;
  ret.y=y;
  return ret;  
}

float Vec2::dot(Vec2 const& rhs) const {
  return (x*rhs.x+y*rhs.y);
}

Vec2 Vec2::operator+(Vec2 const& rhs) const {
  return Vec2::make(x+rhs.x, y+rhs.y);
}

Vec2 Vec2::operator+=(Vec2 const& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  return *this;
}

Vec2 Vec2::operator-(Vec2 const& rhs) const {
  return Vec2::make(x-rhs.x, y-rhs.y);
}

Vec2 Vec2::operator-=(Vec2 const& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  return *this;  
}

Vec2 Vec2::operator-() const {
  return Vec2::make(-x, -y);
}

Vec2 Vec2::operator*(float factor) const {
  return Vec2::make(factor*x, factor*y);
}

Vec2 Vec2::operator*=(float factor) {
  x*=factor;
  y*=factor;
  return *this;
}

float Vec2::length() const {
  return std::sqrt(dot(*this));
}

float Vec2::lengthSquare() const {
  return dot(*this);
}

Vec2 operator*(float f, Vec2 const& lhs) {
  return lhs*f;
}

Vec2 operator*=(float f, Vec2& lhs) {
  return lhs*=f;
}