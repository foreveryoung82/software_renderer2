#include "device.h"
#include <vector>
#include <cassert>
#include "clip.h"
#include "rasterizer.h"
#include "vec2.h"
#include "trapezoid.h"
#include "triangle.h"
#include "framebuffer.h"

Device::Device()
 : framebuffer_(nullptr)
 , rasterizer_(nullptr) {
}

Device::~Device() {
  if (rasterizer_)
    delete rasterizer_;
}

void Device::draw( const Triangle& tri ) {
  assert(framebuffer_);
  std::vector<Vec2> clipped=viewport_clip(tri);
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

void Device::setFramebuffer( Framebuffer& framebuffer ) {
  framebuffer_=&framebuffer;

  if (!rasterizer_)
    rasterizer_=new Rasterizer(*framebuffer_);
}
