//@date:2016.9.18
//@author:yangjie82@gmail.com
//@brief:4x4 matrix
#pragma once

class Vec2;
class Matrix4 {
 public:
  static const Matrix4 kZero;
  static const Matrix4 kIdentity;
  static const Matrix4 make(float e00,float e01,float e02,float e03,
                            float e10,float e11,float e12,float e13,
                            float e20,float e21,float e22,float e23,
                            float e30,float e31,float e32,float e33);
  static const Matrix4 make(float* ma);
  static const Matrix4 makeByColumns(const Vec2& c0,
                                     const Vec2& c1,
                                     const Vec2& c2,
                                     const Vec2& c3);
  static const Matrix4 makeByRows(const Vec2& r0,
                                  const Vec2& r1,
                                  const Vec2& r2,
                                  const Vec2& r3);
  union {
    struct {
      float m00;float m01;float m02;float m03;
      float m10;float m11;float m12;float m13;
      float m20;float m21;float m22;float m23;
      float m30;float m31;float m32;float m33;
    };
    float m[4][4];
  };
};