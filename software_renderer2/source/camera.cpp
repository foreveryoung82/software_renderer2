#include "camera.h"
#include <cmath>

Camera::Camera(ViewParameters const& view,ProjectionParameters perspect)
 : view_(view)
 , projection_(perspect) {
  extraMatrix_      =Matrix4x4::makeIdentity();
  viewMatrix_       =computeViewMatrix_(view_);
  projectionMatrix_ =computeProjectionMatrix_(projection_);
}

Matrix4x4 Camera::computeViewMatrix_(ViewParameters const& view) const {
  Vec3 z=(view.Eye-view.Target).normalized();
  Vec3 x=(view.Up.cross(z)).normalized();
  Vec3 y=z.cross(x);
  Matrix4x4 m;
  m.m[0][0]=x[0];
  m.m[1][0]=x[1];
  m.m[2][0]=x[2];
  m.m[3][0]=-view.Eye.dot(x);
  m.m[0][1]=y[0];
  m.m[1][1]=y[1];
  m.m[2][1]=y[2];
  m.m[3][1]=-view.Eye.dot(y);
  m.m[0][2]=z[0];
  m.m[1][2]=z[1];
  m.m[2][2]=z[2];
  m.m[3][2]=-view.Eye.dot(z);
  m.m[0][3]=0;
  m.m[1][3]=0;
  m.m[2][3]=0;
  m.m[3][3]=1;
  return m;
}

Matrix4x4 Camera::computeProjectionMatrix_(
  ProjectionParameters const& projection) const {
  const f32 t=std::tanf(projection.Fov/2.f);
  const f32 h=projection.Near*t;
  const f32 w=h*projection.Aspect;
  const f32 n=projection.Near;
  const f32 f=projection.Far;
  Matrix4x4 m;
  m.m[0][0]=n/w;
  m.m[1][0]=0;
  m.m[2][0]=0;
  m.m[3][0]=0;
  m.m[0][1]=0;
  m.m[1][1]=n/h;
  m.m[2][1]=0;
  m.m[3][1]=0;
  m.m[0][2]=0;
  m.m[1][2]=0;
  m.m[2][2]=-(f+n)/(f-n);
  m.m[3][2]=-(2.f*f*n)/(f-n);
  m.m[0][3]=0;
  m.m[1][3]=0;
  m.m[2][3]=-1.f;
  m.m[3][3]=0;
  return m;
}

Vec3 Camera::eye() const {
  return view_.Eye;
}

void Camera::setEye(Vec3 const& eye) {
  view_.Eye=eye;
  viewMatrix_=computeViewMatrix_(view_);
}

Vec3 Camera::target() const {
  return view_.Target;
}

void Camera::setTarget(Vec3 const& target) {
  view_.Target=target;
  viewMatrix_=computeViewMatrix_(view_);
}

Vec3 Camera::up() const {
  return view_.Up;
}

void Camera::setUp(Vec3 const& up) {
  view_.Up=up;
  viewMatrix_=computeViewMatrix_(view_);
}

f32 Camera::fov() const {
  return projection_.Fov;
}

void Camera::setFov(f32 fov) {
  projection_.Fov=fov;
  projectionMatrix_=computeProjectionMatrix_(projection_);
}

f32 Camera::aspect() const {
  return projection_.Aspect;
}

void Camera::setAspect(f32 aspect) {
  projection_.Aspect=aspect;
  projectionMatrix_=computeProjectionMatrix_(projection_);
}

f32 Camera::near() const {
  return projection_.Near;
}

void Camera::setNear(f32 near) {
  projection_.Near=near;
  projectionMatrix_=computeProjectionMatrix_(projection_);
}

f32 Camera::far() const {
  return projection_.Far;
}

void Camera::setFar(f32 far) {
  projection_.Far=far;
  projectionMatrix_=computeProjectionMatrix_(projection_);
}

Matrix4x4 Camera::extraMatrix() const {
  return extraMatrix_;
}

void Camera::setExtraMatrix(Matrix4x4 const& extra) {
  extraMatrix_=extra;
}

Matrix4x4 Camera::viewMatrix() const {
  return viewMatrix_;
}

Matrix4x4 Camera::projectionMatrix() const {
  return projectionMatrix_;
}