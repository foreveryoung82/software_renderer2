//@date:2017.4.15
//@author:jieyang@moonton.com
//@brief:struct for matrix 2d
#pragma once
#include <cstdint>
#include <vec2.h>
#include <vec3.h>

// column major
class Matrix3x3 {
public:
  static Matrix3x3 make(Vec3 const& u, Vec3 const& v, Vec3 const& w);
  static Matrix3x3 makeIdentity();
  static Matrix3x3 makeAffine(Vec2 const& u, Vec2 const& v, Vec2 const& w);
  static Matrix3x3 makeTranslation(Vec2 const& t);
  static Matrix3x3 makeScale(Vec2 const& s);
  static Matrix3x3 makeRotation(float radian);
  static Matrix3x3 makeXShear(float factor);
  static Matrix3x3 makeYShear(float factor);

  const float* begin() const;
  float* begin();
  const float* end() const;
  float* end();
  bool operator==(Matrix3x3 const& rhs) const;
  Matrix3x3 operator+(Matrix3x3 const& rhs) const;
  Matrix3x3& operator+=(Matrix3x3 const& rhs);
  Matrix3x3 operator-(Matrix3x3 const& rhs) const;
  Matrix3x3& operator-=(Matrix3x3 const& rhs);
  Matrix3x3 operator-() const;
  Matrix3x3 operator*(float factor) const;
  Matrix3x3& operator*=(float factor);
  Matrix3x3 operator*(Matrix3x3 const& rhs) const;
  Matrix3x3& operator*=(Matrix3x3 const& rhs);
  Vec3 operator*(Vec3 const& rhs) const;
  Vec2 transformVector(Vec2 const& v) const;
  Vec2 transformPoint(Vec2 const& p) const;
  Matrix3x3 inverse() const;
  Matrix3x3 transpose() const;

  float m[3][3];

  float operator()(std::uint8_t col, std::uint8_t row) const;
  Vec3 operator[](std::uint8_t idx);
};