#include "device.h"
#include <vector>
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

  Matrix4x4 mvp=camera_->projectionMatrix()*camera_->viewMatrix();
  Triangle tri2d=Triangle::make(Vec2::make(mvp.transformPoint(tri.p0)),
                                Vec2::make(mvp.transformPoint(tri.p1)),
                                Vec2::make(mvp.transformPoint(tri.p2)));

  std::vector<Vec2> clipped=viewport_clip(tri2d);
  const int clipped_num=clipped.size();
  const int vert_num=clipped.size();
  if (0==vert_num)
    return;
  assert((1!=vert_num) || (2!=vert_num));
  const int triangle_num=(vert_num-2);
  std::vector<Triangle> triangles;
  for (int i=0;i<triangle_num;++i) {
    triangles.push_back(Triangle::make(clipped[0], clipped[i+1], clipped[i+2]));
  }
  for (int i=0;i<triangle_num;++i)
    rasterizer_->draw(triangles[i]);
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
