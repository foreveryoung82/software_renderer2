#include "device.h"
#include <cassert>
#include <algorithm>
#include <vector>
//#include "clip.h"
#include "camera.h"
#include "framebuffer.h"
#include "homogeneousclipper.h"
#include "primitivestream.h"
#include "rasterizer.h"
#include "texture.h"
#include "trapezoid.h"
#include "triangle.h"
#include "triangle3d.h"
#include "vec2.h"

namespace {
std::vector<Vec4> homogenous_clip(Vec4 const& v0,
                                  Vec4 const& v1,
                                  Vec4 const& v2) {
  std::vector<Vec4> stage1=HomogeneousClipper::clipWithInfinitesimalW(v0,
                                                                      v1, 
                                                                      v2);
  const int vertsNumStage1=stage1.size();
  std::vector<Vec4> stage2;
  for(int i=0;i<vertsNumStage1-2;++i) {
    stage2=HomogeneousClipper::clipWithcanonicalViewVolume(stage1[0],
                                                            stage1[i+1],
                                                            stage1[i+2]);
  }

  std::transform(stage2.begin(), // perspective division
    stage2.end(),
    stage2.begin(),
    [](Vec4& vert){
      return vert*(1.f/vert.w);
  });
    
  return stage2;
}

void homogenous_clip(const PrimitiveStream& inStream,
                     PrimitiveStream&       outStream) {
  PrimitiveStream ps(inStream.primitiveType(),inStream.uvDimension());
  HomogeneousClipper::clipWithInfinitesimalW(inStream,ps);
  HomogeneousClipper::clipWithcanonicalViewVolume(ps,outStream);
}

void perspective_division(PrimitiveStream& stream) {
  const int vertNum=stream.vertexNum();
  for(int i=0;i<vertNum;++i) {
    Vec4& xyzw=stream.xyzwAt(i);
    const f32 inverseW=1.f/xyzw.w;
    xyzw=Vec4::make(xyzw.x*inverseW,
                    xyzw.y*inverseW,
                    xyzw.z*inverseW,
                    inverseW);
    std::valarray<f32>& uv=stream.uvAt(i);
    uv*=inverseW;
  }
}

void transform(const PrimitiveStream& inStream,
               PrimitiveStream&       outStream,
               const Matrix4x4&       matrix) {
  const int vertNum=inStream.vertexNum();
  for(int i=0;i<vertNum;++i) {
    const Vec4 xyzw=matrix*inStream.xyzwAt(i);
    const std::valarray<f32>& uv=inStream.uvAt(i);
    outStream.addVertex(xyzw,uv);
  }
  const int primitiveNum=inStream.primitiveNum();
  for(int i=0;i<primitiveNum;++i) {
    u32 idx0=inStream.indexAt(i*3);
    u32 idx1=inStream.indexAt(i*3+1);
    u32 idx2=inStream.indexAt(i*3+2);
    outStream.addPrimitive(idx0,idx1,idx2);
  }
}
}

Device::Device()
 : camera_(nullptr)
 , framebuffer_(nullptr)
 , primitiveStream_(nullptr)
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
  const int polygonVertsNum=polygonVerts.size();
  const int triangleNum=polygonVertsNum-2;
  for(int i=0;i<triangleNum;++i) { // divide convex polygon into triangles
    Triangle tri2d=Triangle::make(
      Vec2::make(polygonVerts[0]),
      Vec2::make(polygonVerts[i+1]),
      Vec2::make(polygonVerts[i+2]));
    rasterizer_->draw(tri2d);
  }
}

void Device::draw() {
  assert(camera_);  
  assert(framebuffer_);
  assert(primitiveStream_);

  Matrix4x4 mvp=camera_->projectionMatrix()*
    camera_->viewMatrix()*
    camera_->extraMatrix();
  PrimitiveStream inStream(PrimitiveType::TriangleList,3);

  transform(*primitiveStream_,inStream,mvp);
  PrimitiveStream outStream(PrimitiveType::TriangleList,3);
  homogenous_clip(inStream,outStream);
  perspective_division(outStream);

  rasterizer_->draw(outStream);
}

void Device::blit(const Texture& tex) {
  for(int y=0;y<tex.height();++y) {
    if(y>=framebuffer_->height())
      break;
    for(int x=0;x<tex.width();++x) {
      if(x>=framebuffer_->width())
        continue;
      framebuffer_->setPixel(x,y,tex.colorAt(x,y).Value());
    }
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

void Device::setPrimitiveStream(const PrimitiveStream& primitiveStream) {
  primitiveStream_=&primitiveStream;
}
