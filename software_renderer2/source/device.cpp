#include "device.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "clip.h"
#include "rasterizer.h"
#include "vec2.h"
#include "trapezoid.h"
#include "triangle.h"
#include "triangle3d.h"
#include "framebuffer.h"
#include "camera.h"

Device::Device()
 : camera_(nullptr)
 , framebuffer_(nullptr)
 , rasterizer_(nullptr) {
}

Device::~Device() {
  if (rasterizer_)
    delete rasterizer_;
}

void Device::draw( const Triangle3D& tri ) {
  assert(camera_);  
  assert(framebuffer_);

  Matrix4x4 mvp=camera_->projectionMatrix()*
                  camera_->viewMatrix()*
                  camera_->extraMatrix();
  Vec4 v0=mvp*Vec4::make(tri.p0, 1.f);
  Vec4 v1=mvp*Vec4::make(tri.p1, 1.f);
  Vec4 v2=mvp*Vec4::make(tri.p2, 1.f);
  std::vector<Vec4> polygonVerts=homogenous_clip(v0,v1,v2);
  std::transform(polygonVerts.begin(), // perspective division
                 polygonVerts.end(),
                 polygonVerts.begin(),
                 [](Vec4& vert){
                    return vert*(1.f/vert.w);
                 });
  const int polygonVertsNum=polygonVerts.size();
  const int triangleNum=polygonVertsNum-2;
  for(int i=0;i<triangleNum;++i) { // divide convex polygon into triangles
    Triangle tri2d=Triangle::make(
      Vec2::make(polygonVerts[0]),
      Vec2::make(polygonVerts[i]),
      Vec2::make(polygonVerts[(i+1)%polygonVertsNum]));
    rasterizer_->draw(tri2d);
  }
}

void Device::clear() {
  assert(framebuffer_);
  framebuffer_->clear(0);
}

void Device::present() {
  assert(framebuffer_);
}

void Device::setCamera(Camera& camera) {
  camera_=&camera;
}

void Device::setFramebuffer( Framebuffer& framebuffer ) {
  framebuffer_=&framebuffer;

  if (!rasterizer_)
    rasterizer_=new Rasterizer(*framebuffer_);
}
