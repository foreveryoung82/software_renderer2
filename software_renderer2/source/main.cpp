#include <iostream>
#include <iomanip>
#include "application.h"
#include "framebuffer.h"
#include "device.h"
#include "triangle.h"
#include "camera.h"
#include "matrix3x3.h"
#include "matrix4x4.h"
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include "triangle3d.h"

void Dump(Vec4 const& v) {
  std::cout<<std::setw(8)<<v.x
    <<std::setw(8)<<v.y
    <<std::setw(8)<<v.z
    <<std::setw(8)<<v.w
    <<std::endl;
}

void Dump(Matrix4x4 const& m) {
  for(int r=0;r<4;++r) {
    std::cout<<std::setw(12)<<m.m[0][r]
    <<std::setw(12)<<m.m[1][r]
    <<std::setw(12)<<m.m[2][r]
    <<std::setw(12)<<m.m[3][r]
    <<std::endl;
  }
}

void main() {
  Device device;
  Application app;

  Camera::ViewParameters vp;
  vp.Eye    = Vec3::make(0,0,1.f);
  vp.Target = Vec3::make(0,0,-1);
  vp.Up     = Vec3::kUnitY;
  Camera::ProjectionParameters pp;
  pp.Aspect = 1.f;
  pp.Far    = 100.f;
  pp.Fov    = 3.1415926f/2.f;
  pp.Near   = 1.f;
  Camera camera=Camera(vp,pp);

  Triangle3D tri=Triangle3D::make(Vec3::make(1.5f,1.5f,-2.f),
    Vec3::make(-1.5f,1.5f,-2.f),
    Vec3::make(1.5f,-1.5f,-2.f));

  app.setOnFrameBeginEvent([&device,&camera,&tri](Framebuffer& fb){
    Matrix4x4 rotation=Matrix4x4::makeRotation(3.1415926f/180.f,Vec3::kUnitY);
    camera.setEye(rotation.transformPoint(camera.eye()));

    device.setCamera(camera);
    device.setFramebuffer(fb);

    device.clear();
    device.draw(tri);
  });
  app.setup(640,480);
  app.run();
  app.teardown();
}

//#include <vector>
//#include <iostream>
//#include <iomanip>
//#include "clip.h"
//#include "vec4.h"
//void Dump(Vec4 const& v) {
//  std::cout<<std::setw(8)<<v.x
//    <<std::setw(8)<<v.y
//    <<std::setw(8)<<v.z
//    <<std::setw(8)<<v.w
//    <<std::endl;
//}
//void main() {
//  std::vector<Vec4> clipResult=homogenous_clip(Vec4::make(-10.f,-10.f,-10.f,1.f),
//                                               Vec4::make(10.f,10.f,10.f,1.f));
//  for(auto v:clipResult) {
//    Dump(v);
//  }
//}