//@date:2017.6.10
//@author:yangjie82@gmail.com
//@brief:triangle class
#pragma once
#include "base.h"
#include "vec3.h"

//逆时针方向顶点描述的三角形
class Triangle3D {
public:
  static Triangle3D make(Vec3 const& p0, Vec3 const& p1, Vec3 const& p2);
  union {
    struct {
      Vec3 p0;
      Vec3 p1;
      Vec3 p2;
    };
    Vec3 m[3];
  };
  Vec3& operator[](u8 idx) {return m[idx];}
  const Vec3& operator[](u8 idx) const {return m[idx];}
  //Triangle scale(f32 scale_x, f32 scale_y) const;
};