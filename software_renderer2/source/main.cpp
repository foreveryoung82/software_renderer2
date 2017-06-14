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
#include "texture.h"

void Dump(Vec4 const& v) {
  std::cout<<std::setw(8)<<v.x
    <<std::setw(8)<<v.y
    <<std::setw(8)<<v.z
    <<std::setw(8)<<v.w
    <<std::endl;
}

void Dump(Vec3 const& v) {
  std::cout<<std::setw(8)<<v.x
    <<std::setw(8)<<v.y
    <<std::setw(8)<<v.z
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
  vp.Eye    = Vec3::make(0,0,3.f);
  vp.Target = Vec3::make(0,0,-1);
  vp.Up     = Vec3::kUnitY;
  Camera::ProjectionParameters pp;
  pp.Aspect = 1.f;
  pp.Far    = 3.5f;
  pp.Fov    = 3.1415926f/2.f;
  pp.Near   = 1.f;
  Camera camera=Camera(vp,pp);

  Triangle3D tri=Triangle3D::make(Vec3::make(1.f,1.f,0),
    Vec3::make(-1.f,1.f,0),
    Vec3::make(0.f,-1.f,0));

  f32 rotationStep=3.1415926f/180.f;
  f32 frames=0;


  Texture tex("data/test.png");

  app.setOnFrameBeginEvent([&device,&camera,&tri,&frames,&tex,rotationStep]
                            (Framebuffer& fb){
    Matrix4x4 rotation=Matrix4x4::makeRotation(frames*rotationStep,Vec3::kUnitY);
    frames+=1.f;
    rotation=Matrix4x4::makeTranslation(Vec3::make(0.f,-1.5f,0))*
               rotation*
               Matrix4x4::makeTranslation(Vec3::make(0.f,1.5f,0));
    Dump(rotation.transformPoint(tri.p0));
    Dump(rotation.transformPoint(tri.p1));
    Dump(rotation.transformPoint(tri.p2));
    //camera.setEye(rotation.transformPoint(camera.eye()));
    camera.setExtraMatrix(rotation);    

    device.setCamera(camera);
    device.setFramebuffer(fb);

    device.clear();
    device.blit(tex);
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
//    Vec4::make(10.f,10.f,10.f,1.f));
//  for(auto v:clipResult) {
//    Dump(v);
//  }
//}