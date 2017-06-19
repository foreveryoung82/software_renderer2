//@date:2017.6.19
//@author:jieyang@moonton.com
//@brief:arc ball class
#pragma once
#include "quaternion.h"
#include "vec3.h"

// arc ball is a virtual ball to make rotation more intuitive
class ArcBall {
 public:
  explicit ArcBall(int width,int height);
  virtual ~ArcBall();
  virtual void beginDrag(int x,int y);
  virtual void onDrag(int x,int y);
  virtual void endDrag();
  virtual const Quaternion& rotation() const;
 private:
  f32 radius_;
  f32 centerX_;
  f32 centerY_;
  Vec3 start_;
  Vec3 current_;
  Quaternion rotation_;

  Vec3 projectScreenToVirtualBall(int x,int y);
};