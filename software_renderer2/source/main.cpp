//#include "application.h"
//#include "framebuffer.h"
//#include "device.h"
//#include "triangle.h"
//#include "matrix3x3.h"
//
//void main() {
//  Device device;
//  Application app;
//  Triangle tri=Triangle::make(Vec2::make(0.3f,1.3f),
//    Vec2::make(-1.f,-1.5f),
//    Vec2::make(0.6f,-0.8f));
//
//  app.setOnFrameBeginEvent([&device,&tri](Framebuffer& fb){
//    device.setFramebuffer(fb);
//
//    Matrix3x3 rotationQuarterPi=Matrix3x3::makeRotation(3.1415926f/180.f);
//    tri.p0=rotationQuarterPi.transformPoint(tri.p0);
//    tri.p1=rotationQuarterPi.transformPoint(tri.p1);
//    tri.p2=rotationQuarterPi.transformPoint(tri.p2);
//    device.clear();
//    device.draw(tri);
//  });
//  app.setup(640,480);
//  app.run();
//  app.teardown();
//}

#include <iostream>
#include <iomanip>
#include "matrix4x4.h"
#include "matrix3x3.h"
#include "vec3.h"

using namespace std;
void Dump(Matrix4x4 const& m) {
  for(int c=0;c<4;++c) {
    for(int r=0;r<4;++r) {
      cout<<setw(12)<<setiosflags(ios::left)<<m.m[c][r];
    }
    cout<<endl;
  }
}
void Dump(Matrix3x3 const& m) {
  for(int c=0;c<3;++c) {
    for(int r=0;r<3;++r) {
      cout<<setw(12)<<setiosflags(ios::left)<<m.m[c][r];
    }
    cout<<endl;
  }
}
void main() {
  Matrix4x4 m=Matrix4x4::makeRotation(1.f,Vec3::kUnitX);
  m=Matrix4x4::makeTranslation(Vec3::make(4,5,6))*m;
  Matrix4x4 ret=m*m.inverse();

  //Matrix3x3 m=Matrix3x3::makeRotation(1.f);
  //Matrix3x3 ret=m*m.inverse();
  Dump(ret);
  cout<<ret.determinant()<<endl;
}