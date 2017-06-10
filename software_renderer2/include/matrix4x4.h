//@date:2017.4.15
//@author:jieyang@moonton.com
//@brief:struct for matrix 2d
#pragma once
#include "base.h"
#include "vec3.h"
#include "vec4.h"

// column major
class Matrix4x4 {
public:
  static Matrix4x4 make(Vec4 const& x,
                        Vec4 const& y,
                        Vec4 const& z,
                        Vec4 const& w);
  static Matrix4x4 makeIdentity();
  static Matrix4x4 makeAffine(Vec3 const& x,
                              Vec3 const& y,
                              Vec3 const& z,
                              Vec3 const& w);
  static Matrix4x4 makeTranslation(Vec3 const& t);
  static Matrix4x4 makeScale(Vec3 const& s);
  static Matrix4x4 makeRotation(f32 radian,Vec3 const& unitAxis);
  //static Matrix4x4 makeXShear(f32 factor);
  //static Matrix4x4 makeYShear(f32 factor);
  //static Matrix4x4 makeZShear(f32 factor);

  const f32* begin() const;
  f32* begin();
  const f32* end() const;
  f32* end();
  bool operator==(Matrix4x4 const& rhs) const;
  Matrix4x4 operator+(Matrix4x4 const& rhs) const;
  Matrix4x4& operator+=(Matrix4x4 const& rhs);
  Matrix4x4 operator-(Matrix4x4 const& rhs) const;
  Matrix4x4& operator-=(Matrix4x4 const& rhs);
  Matrix4x4 operator-() const;
  Matrix4x4 operator*(f32 factor) const;
  Matrix4x4& operator*=(f32 factor);
  Matrix4x4 operator*(Matrix4x4 const& rhs) const;
  Matrix4x4& operator*=(Matrix4x4 const& rhs);
  Vec4 operator*(Vec4 const& rhs) const;
  Vec3 transformVector(Vec3 const& v) const;
  Vec3 transformPoint(Vec3 const& p) const;
  Matrix4x4 inverse() const;
  Matrix4x4 transpose() const;
  f32 determinant() const;
  f32 cofactor(u8 r,u8 c) const;
  f32 algebraicCofactor(u8 r,u8 c) const;

  f32 m[4][4];

  f32 operator()(u8 col, u8 row) const;
  Vec4 operator[](u8 idx);
};