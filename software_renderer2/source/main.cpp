#include <iostream>
#include <iomanip>
#include "application.h"
#include "camera.h"
#include "device.h"
#include "matrix3x3.h"
#include "matrix4x4.h"
#include "framebuffer.h"
#include "primitivestream.h"
#include "texture.h"
#include "triangle.h"
#include "triangle3d.h"
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"

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
  int x=1;
  std::move(x);
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

  PrimitiveStream ps(PrimitiveType::TriangleList,2);
  //f32 red[3]={1,0,0};
  //f32 green[3]={0,1,0};
  //f32 blue[3]={0,0,1};
  Vec2 uvQuad[4]={
    Vec2::make(1,1),
    Vec2::make(0,1),
    Vec2::make(0,0),
    Vec2::make(1,0),
  };
  Vec4 xyzwQuad[4]={
    Vec4::make(1,1,0,1),
    Vec4::make(-1,1,0,1),
    Vec4::make(-1,-1,0,1),
    Vec4::make(1,-1,0,1),
  };
  ps.addVertex(xyzwQuad[0],std::valarray<f32>(uvQuad[0].m,2));
  ps.addVertex(xyzwQuad[1],std::valarray<f32>(uvQuad[1].m,2));
  ps.addVertex(xyzwQuad[2],std::valarray<f32>(uvQuad[2].m,2));
  ps.addVertex(xyzwQuad[3],std::valarray<f32>(uvQuad[3].m,2));
  ps.addPrimitive(0,1,2);
  ps.addPrimitive(0,2,3);

  f32 rotationStep=3.1415926f/180.f;
  f32 frames=0;


  Texture tex("data/test.png");

  app.setOnFrameBeginEvent([&device,&camera,&frames,&tex,&ps,rotationStep]
                            (Framebuffer& fb){
    Matrix4x4 rotation=Matrix4x4::makeRotation(frames*rotationStep,Vec3::kUnitY);
    frames+=1.f;
    rotation=Matrix4x4::makeTranslation(Vec3::make(0.f,-1.5f,0))*
               rotation*
               Matrix4x4::makeTranslation(Vec3::make(0.f,1.5f,0));
    camera.setExtraMatrix(rotation);    

    device.setCamera(camera);
    device.setFramebuffer(fb);
    device.setPrimitiveStream(ps);

    device.clear();
    //device.blit(tex);
    device.setTexture(tex);
    //device.draw(tri);
    device.draw();
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