#include <iostream>
#include "triangle.h"
#include "vec2.h"
#include "trapezoid.h"
#include "rasterizer.h"
void main() {
  // don't forget when triangle is totally in/out clip rect

  //Triangle tri=Triangle::make(Vec2::make(0,0),
  //                            Vec2::make(1,1),
  //                            Vec2::make(0,2));
  //Trapezoid trapezoids[2];
  //int n=divide_into_trapezoids(tri, trapezoids);
  //std::cout<<n<<std::endl;

  Rasterizer rasterizer(8,8);
  //rasterizer.setPixelAt(0,0,0xFF);
  //rasterizer.setPixelAt(1,1,0xFF);
  //rasterizer.setPixelAt(2,2,0xFF);
  //rasterizer.setPixelAt(3,3,0xFF);
  Triangle tri=Triangle::make(Vec2::make(0,0),
                              Vec2::make(4,4),
                              Vec2::make(0,7));
  rasterizer.draw(tri);
  rasterizer.present();
}
