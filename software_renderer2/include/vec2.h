//@date:2016.4.23
//@author:jieyang@moonton.com
//@brief:struct for vector 2d
#pragma once
#include <cstdint>

class Vec3;
class Vec2 {
 public:
  static const Vec2 kZero;
  static const Vec2 kUnitX;
  static const Vec2 kUnitY;
  static Vec2 make(float x,float y);
  static Vec2 make(const Vec3& v);
  union {
    struct {
      float x;
      float y;
    };
    float m[2];
  };

  //Vec2& operator=(Vec2 const& rhs);
  bool operator==(Vec2 const& rhs) const;
  float dot(Vec2 const& rhs) const;
  Vec2 operator+(Vec2 const& rhs) const;
  Vec2& operator+=(Vec2 const& rhs);
  Vec2 operator-(Vec2 const& rhs) const;
  Vec2& operator-=(Vec2 const& rhs);
  Vec2 operator-() const;
  Vec2 operator*(float factor) const;
  Vec2& operator*=(float factor);
  float& operator[](std::uint8_t idx) {return m[idx];}
  const float& operator[](std::uint8_t idx) const {return m[idx];};
  //float length() const;
  //float lengthSquare() const;
};

Vec2 operator*(float f, Vec2 const& lhs);
Vec2 operator*=(float f, Vec2& lhs);