//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for vector 2d
#pragma once
#include "base.h"

class Vec3;
class Vec2 {
 public:
  static const Vec2 kZero;
  static const Vec2 kUnitX;
  static const Vec2 kUnitY;
  static Vec2 make(f32 x,f32 y);
  static Vec2 make(const Vec3& v);
  union {
    struct {
      f32 x;
      f32 y;
    };
    f32 m[2];
  };

  //Vec2& operator=(Vec2 const& rhs);
  bool operator==(Vec2 const& rhs) const;
  f32 dot(Vec2 const& rhs) const;
  Vec2 operator+(Vec2 const& rhs) const;
  Vec2& operator+=(Vec2 const& rhs);
  Vec2 operator-(Vec2 const& rhs) const;
  Vec2& operator-=(Vec2 const& rhs);
  Vec2 operator-() const;
  Vec2 operator*(f32 factor) const;
  Vec2& operator*=(f32 factor);
  f32& operator[](u8 idx) {return m[idx];}
  const f32& operator[](u8 idx) const {return m[idx];};
  //f32 length() const;
  //f32 lengthSquare() const;
};

Vec2 operator*(f32 f, Vec2 const& lhs);
Vec2 operator*=(f32 f, Vec2& lhs);