#include <iostream>
#include <vector>
#include <cassert>
#include "triangle.h"
#include "vec2.h"
#include "trapezoid.h"
#include "rasterizer.h"
#include "clip.h"
void main() {
  // don't forget when triangle is totally in/out clip rect

  //Triangle tri=Triangle::make(Vec2::make(0,0),
  //  Vec2::make(1,0),
  //  Vec2::make(2,1));
  //Triangle tri=Triangle::make(Vec2::make(0,0),
  //  Vec2::make(1,1),
  //  Vec2::make(0,1));
  //Triangle tri=Triangle::make(Vec2::make(0,-2),
  //  Vec2::make(2,2),
  //  Vec2::make(-2,0.5));
  //Trapezoid trapezoids[2];
  //int n=divide_into_trapezoids(tri, trapezoids);
  //std::cout<<n<<std::endl;

  //Rasterizer rasterizer(8,8);
  //Triangle tri=Triangle::make(Vec2::make(-1,-0.75),
  //                            Vec2::make(1,0),
  //                            Vec2::make(1,1));
  //rasterizer.draw(tri);
  //rasterizer.present();

  Triangle tri=Triangle::make(Vec2::make(0.3,1.3),
    Vec2::make(-1,-1.5),
    Vec2::make(0.6,-0.8));

  std::vector<Vec2> clipped=viewport_clip(tri);
  const int clipped_num=clipped.size();
  for (int i=0;i<clipped_num;++i) {
    std::cout<<'('<<clipped[i].x<<','<<clipped[i].y<<')'<<std::endl;
  }
  const int vert_num=clipped.size();
  if (0==vert_num)
    return;
  assert((1!=vert_num) || (2!=vert_num));
  const int triangle_num=(vert_num-2);
  std::vector<Triangle> triangles;
  for (int i=0;i<triangle_num;++i) {
    triangles.push_back(
      Triangle::make(clipped[0],
                     clipped[i+1],
                     clipped[i+2]));
  }
  Rasterizer rasterizer(8,8);
  for (int i=0;i<triangle_num;++i)
    rasterizer.draw(triangles[i]);
  rasterizer.present();
}
