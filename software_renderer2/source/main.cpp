#include "application.h"
#include "framebuffer.h"
#include "device.h"
#include "triangle.h"
#include "matrix3x3.h"

void main() {
  Device device;
  Application app;
  Triangle tri=Triangle::make(Vec2::make(0.3f,1.3f),
    Vec2::make(-1.f,-1.5f),
    Vec2::make(0.6f,-0.8f));

  app.setOnFrameBeginEvent([&device,&tri](Framebuffer& fb){
    device.setFramebuffer(fb);

    Matrix3x3 rotationQuarterPi=Matrix3x3::makeRotation(3.1415926f/180.f);
    tri.p0=rotationQuarterPi.transformPoint(tri.p0);
    tri.p1=rotationQuarterPi.transformPoint(tri.p1);
    tri.p2=rotationQuarterPi.transformPoint(tri.p2);
    device.clear();
    device.draw(tri);
  });
  app.setup(640,480);
  app.run();
  app.teardown();
}