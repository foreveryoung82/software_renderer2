//@date:2017.6.8
//@author:yangjie82@gmail.com
//@brief:camera
#pragma once
#include "base.h"
#include "vec4.h"

// camera class for perspective projection
class Camera {
 public:
  explicit Camera(f32 fov, f32 aspect, f32 near, f32 far);
  //f32 fov() const;
  //void setFov(f32 fov);
  //f32 aspect() const;
  //void setAspect(f32 aspect);
  //f32 near() const;
  //void setNear(f32 near);
  //f32 far() const;
  //void setFar(f32 far);
  Vec4 transform(Vec4 const& v);

 private:
  //f32 fov_;
  //f32 aspect_;
  //f32 near_;
  //f32 far_;
  f32 matrix_[4][4];  // column major
};