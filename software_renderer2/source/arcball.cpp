#include "arcball.h"
#include <cmath>
#include <algorithm>

ArcBall::ArcBall(int width,int height)
 //, radius_()
 : centerX_(width*0.5f)
 , centerY_(height*0.5f)
 , start_(Vec3::kZero)
 , current_(Vec3::kZero)
 , rotation_(Vec4::kUnitW) {
  radius_=static_cast<f32>(std::min(width,height));
}

ArcBall::~ArcBall() {
}

void ArcBall::beginDrag(int x,int y) {
  start_    = projectScreenToVirtualBall(x,y);
  current_  = start_;
  //rotation_ = Vec4::kUnitW;
}

void ArcBall::onDrag(int x,int y) {
  current_  = projectScreenToVirtualBall(x,y);
  rotation_ = Quaternion::computeShortestRotation(start_, current_);
}

void ArcBall::endDrag() {
  rotation_=Vec4::kUnitW;
}

const Quaternion& ArcBall::rotation() const {
  return rotation_;
}

Vec3 ArcBall::projectScreenToVirtualBall(int x,int y) {
  // if start point is out of virtual ball, project it into ball edge
  const f32 dx=(x-centerX_);
  const f32 dy=(y-centerY_);
  const f32 r2=radius_*radius_;
  const f32 len2=dx*dx+dy*dy;
  //const f32 len=std::sqrt(len2);
  Vec3 p;
  const f32 z=std::sqrt(std::max(0.f, r2-len2));
  p=Vec3::make(dx, dy, z).normalized();

  return p;
}
