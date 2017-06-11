//@date:2017.6.8
//@author:yangjie82@gmail.com
//@brief:camera
#pragma once
#include "base.h"
#include "vec3.h"
#include "matrix4x4.h"

// camera class for perspective projection
class Camera {
 public:
  struct ViewParameters {
    Vec3 Eye;
    Vec3 Target;
    Vec3 Up;
  };
  struct ProjectionParameters {
    f32 Fov;
    f32 Aspect;
    f32 Near;
    f32 Far;
  };

  explicit Camera(ViewParameters const& view,ProjectionParameters projection);
  Vec3 eye() const;
  void setEye(Vec3 const& eye);
  Vec3 target() const;
  void setTarget(Vec3 const& target);
  Vec3 up() const;
  void setUp(Vec3 const& up);
  f32 fov() const;
  void setFov(f32 fov);
  f32 aspect() const;
  void setAspect(f32 aspect);
  f32 near() const;
  void setNear(f32 near);
  f32 far() const;
  void setFar(f32 Far);
  Matrix4x4 extraMatrix() const;
  void setExtraMatrix(Matrix4x4 const& extra);
  Matrix4x4 viewMatrix() const;
  Matrix4x4 projectionMatrix() const;

 private:
  ViewParameters        view_;
  ProjectionParameters  projection_;
  Matrix4x4             extraMatrix_;
  Matrix4x4             viewMatrix_;
  Matrix4x4             projectionMatrix_;

  Matrix4x4 computeViewMatrix_(ViewParameters const& view) const;
  Matrix4x4 computeProjectionMatrix_(ProjectionParameters const& projection) 
              const;
};