#include <iostream>
#include <vector>
#include "triangle.h"
#include "vec2.h"
#include "trapezoid.h"
#include "rasterizer.h"
#include "clip.h"
void main() {
  // don't forget when triangle is totally in/out clip rect

  Triangle tri=Triangle::make(Vec2::make(0,-2),
    Vec2::make(2,2),
    Vec2::make(-2,0.5));
  //Trapezoid trapezoids[2];
  //int n=divide_into_trapezoids(tri, trapezoids);
  //std::cout<<n<<std::endl;

  //Rasterizer rasterizer(8,8);
  ////rasterizer.setPixelAt(0,0,0xFF);
  ////rasterizer.setPixelAt(1,1,0xFF);
  ////rasterizer.setPixelAt(2,2,0xFF);
  ////rasterizer.setPixelAt(3,3,0xFF);
  //Triangle tri=Triangle::make(Vec2::make(0,0),
  //                            Vec2::make(4,-5),
  //                            Vec2::make(7,0));
  //rasterizer.draw(tri);
  //rasterizer.present();
  std::vector<Vec2> clipped=viewport_clip(tri);
  const int clipped_num=clipped.size();
  for (int i=0;i<clipped_num;++i) {
    std::cout<<'('<<clipped[i].x<<','<<clipped[i].y<<')'<<std::endl;
  }
}
