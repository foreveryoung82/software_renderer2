//#include <iostream>
//#include <vector>
//#include <cassert>
//#include "triangle.h"
//#include "vec2.h"
//#include "trapezoid.h"
//#include "rasterizer.h"
//#include "clip.h"
//void main() {
//  Triangle tri=Triangle::make(Vec2::make(0.3,1.3),
//    Vec2::make(-1,-1.5),
//    Vec2::make(0.6,-0.8));
//
//  std::vector<Vec2> clipped=viewport_clip(tri);
//  const int clipped_num=clipped.size();
//  for (int i=0;i<clipped_num;++i) {
//    std::cout<<'('<<clipped[i].x<<','<<clipped[i].y<<')'<<std::endl;
//  }
//  const int vert_num=clipped.size();
//  if (0==vert_num)
//    return;
//  assert((1!=vert_num) || (2!=vert_num));
//  const int triangle_num=(vert_num-2);
//  std::vector<Triangle> triangles;
//  for (int i=0;i<triangle_num;++i) {
//    triangles.push_back(
//      Triangle::make(clipped[0],
//                     clipped[i+1],
//                     clipped[i+2]));
//  }
//  Rasterizer rasterizer(8,8);
//  for (int i=0;i<triangle_num;++i)
//    rasterizer.draw(triangles[i]);
//  rasterizer.present();
//}
//#include <windows.h>
//#include "device.h"
//#include "deviceparameters.h"
//extern HINSTANCE happ=0;
//int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,PSTR,int) {
//  happ=hinstance;
//  DeviceParameters param;
//  param.framebufferWidth=640;
//  param.framebufferHeight=480;
//  Device device(param);
//}
#include "application.h"
#include "framebuffer.h"
void main() {
  //DeviceParameters param;
  //param.framebufferWidth=640;
  //param.framebufferHeight=480;
  //Device device(param);
  int x=0;
  int y=0;
  Application app;
  app.setOnFrameBeginEvent([&x,&y](Framebuffer& fb){
    if (x>=640||y>=480)
      return;
    fb.setPixel(x,y,0xFFFF00FF);
    x++;
    y++;
  });
  app.setup(640,480);
  app.run();
  app.teardown();
}