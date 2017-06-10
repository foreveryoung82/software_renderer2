//@date:2017.6.8
//@author:jieyang@moonton.com
//@brief:struct for vector 4d
#pragma once
#include "base.h"

class Vec4 {
public:
  static const Vec4 kZero;
  static const Vec4 kUnitX;
  static const Vec4 kUnitY;
  static const Vec4 kUnitZ;
  static const Vec4 kUnitW;
  static Vec4 make(f32 x,f32 y,f32 z, f32 w);
  union {
    struct {
      f32 x;
      f32 y;
      f32 z;
      f32 w;
    };
    f32 m[4];
  };

  const f32* begin() const;
  f32* begin();
  const f32* end() const;
  f32* end();
  bool operator==(Vec4 const& rhs) const;
  f32 dot(Vec4 const& rhs) const;
  Vec4 operator+(Vec4 const& rhs) const;
  Vec4& operator+=(Vec4 const& rhs);
  Vec4 operator-(Vec4 const& rhs) const;
  Vec4& operator-=(Vec4 const& rhs);
  Vec4 operator-() const;
  Vec4 operator*(f32 factor) const;
  Vec4& operator*=(f32 factor);
  f32& operator[](u8 idx) {return m[idx];}
  const f32& operator[](u8 idx) const {return m[idx];};
  f32 length() const;
  f32 lengthSquare() const;
  Vec4 normalized() const;
};

Vec4 operator*(f32 f, Vec4 const& lhs);
Vec4 operator*=(f32 f, Vec4& lhs);