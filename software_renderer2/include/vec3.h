//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for vector 2d
#pragma once
#include <cstdint>

class Vec3 {
public:
  static const Vec3 kZero;
  static const Vec3 kUnitX;
  static const Vec3 kUnitY;
  static const Vec3 kUnitZ;
  static Vec3 make(float x,float y,float z);
  union {
    struct {
      float x;
      float y;
      float z;
    };
    float m[3];
  };

  //Vec3& operator=(Vec3 const& rhs);
  bool operator==(Vec3 const& rhs) const;
  float dot(Vec3 const& rhs) const;
  Vec3 operator+(Vec3 const& rhs) const;
  Vec3& operator+=(Vec3 const& rhs);
  Vec3 operator-(Vec3 const& rhs) const;
  Vec3& operator-=(Vec3 const& rhs);
  Vec3 operator-() const;
  Vec3 operator*(float factor) const;
  Vec3& operator*=(float factor);
  float& operator[](std::uint8_t idx) {return m[idx];}
  const float& operator[](std::uint8_t idx) const {return m[idx];};
  //float length() const;
  //float lengthSquare() const;
};

Vec3 operator*(float f, Vec3 const& lhs);
Vec3 operator*=(float f, Vec3& lhs);