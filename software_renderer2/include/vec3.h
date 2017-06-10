//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for vector 2d
#pragma once
#include "base.h"

class Vec4;
class Vec3 {
public:
  static const Vec3 kZero;
  static const Vec3 kUnitX;
  static const Vec3 kUnitY;
  static const Vec3 kUnitZ;
  static Vec3 make(f32 x,f32 y,f32 z);
  static Vec3 make(Vec4 const& v4);
  union {
    struct {
      f32 x;
      f32 y;
      f32 z;
    };
    f32 m[3];
  };

  //Vec3& operator=(Vec3 const& rhs);
  const f32* begin() const;
  f32* begin();
  const f32* end() const;
  f32* end();
  bool operator==(Vec3 const& rhs) const;
  f32 dot(Vec3 const& rhs) const;
  Vec3 cross(Vec3 const& rhs) const;
  Vec3 operator+(Vec3 const& rhs) const;
  Vec3& operator+=(Vec3 const& rhs);
  Vec3 operator-(Vec3 const& rhs) const;
  Vec3& operator-=(Vec3 const& rhs);
  Vec3 operator-() const;
  Vec3 operator*(f32 factor) const;
  Vec3& operator*=(f32 factor);
  f32& operator[](u8 idx) {return m[idx];}
  const f32& operator[](u8 idx) const {return m[idx];};
  f32 length() const;
  f32 lengthSquare() const;
  Vec3 normalized() const;
};

Vec3 operator*(f32 f, Vec3 const& lhs);
Vec3 operator*=(f32 f, Vec3& lhs);