#include "application.h"
#include "framebuffer.h"
#include "device.h"
#include "triangle.h"
void main() {
  Device device;
  Application app;
  Triangle tri=Triangle::make(Vec2::make(0.3f,1.3f),
    Vec2::make(-1.f,-1.5f),
    Vec2::make(0.6f,-0.8f));
  app.setOnFrameBeginEvent([&device,&tri](Framebuffer& fb){
    device.setFramebuffer(fb);
    device.draw(tri);
  });
  app.setup(640,480);
  app.run();
  app.teardown();
}