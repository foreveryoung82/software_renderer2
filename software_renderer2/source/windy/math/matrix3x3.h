//@date:2017.4.15
//@author:jieyang@moonton.com
//@brief:struct for matrix 2d
#pragma once
#include "windy/math/vec2.h"
#include "windy/math/vec3.h"
#include "windy/base/basetype.h"

namespace windy {
// column major
class Matrix3x3 {
public:
  static Matrix3x3 make(Vec3 const& u, Vec3 const& v, Vec3 const& w);
  static Matrix3x3 makeIdentity();
  static Matrix3x3 makeAffine(Vec2 const& u, Vec2 const& v, Vec2 const& w);
  static Matrix3x3 makeTranslation(Vec2 const& t);
  static Matrix3x3 makeScale(Vec2 const& s);
  static Matrix3x3 makeRotation(f32 radian);
  static Matrix3x3 makeXShear(f32 factor);
  static Matrix3x3 makeYShear(f32 factor);

  const f32* begin() const;
  f32* begin();
  const f32* end() const;
  f32* end();
  bool operator==(Matrix3x3 const& rhs) const;
  Matrix3x3 operator+(Matrix3x3 const& rhs) const;
  Matrix3x3& operator+=(Matrix3x3 const& rhs);
  Matrix3x3 operator-(Matrix3x3 const& rhs) const;
  Matrix3x3& operator-=(Matrix3x3 const& rhs);
  Matrix3x3 operator-() const;
  Matrix3x3 operator*(f32 factor) const;
  Matrix3x3& operator*=(f32 factor);
  Matrix3x3 operator*(Matrix3x3 const& rhs) const;
  Matrix3x3& operator*=(Matrix3x3 const& rhs);
  Vec3 operator*(Vec3 const& rhs) const;
  Vec2 transformVector(Vec2 const& v) const;
  Vec2 transformPoint(Vec2 const& p) const;
  Matrix3x3 inverse() const;
  Matrix3x3 transpose() const;
  f32 determinant() const;
  f32 cofactor(u8 r, u8 c) const;
  f32 algebraicCofactor(u8 r, u8 c) const;

  f32 m[3][3];

  f32 operator()(u8 col, u8 row) const;
  Vec3 operator[](u8 idx);
};
}