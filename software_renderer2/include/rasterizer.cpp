#include "rasterizer.h"
#include <cassert>
#include <iostream>
#include <vector>
#include "rect.h"
#include "trapezoid.h"
#include "intersectresult.h"
#include "intersect.h"
#include "clip.h"
#include "triangle.h"

Rasterizer::Rasterizer(int width, int height)
 :width_(width),
  height_(height),
  buffer_(width*height) {
}

Rasterizer::~Rasterizer() {
}

int Rasterizer::width() const {
  return width_;
}

int Rasterizer::height() const {
  return height_;
}

void Rasterizer::setPixelAt( int x, int y, int color ) {
  assert(x<width_ && x>=0);
  assert(y<height_ && y>=0);

  buffer_[y*width_+x]=color;
}

int Rasterizer::getPixelAt( int x, int y ) const {
  assert(x<width_ && x>=0);
  assert(y<height_ && y>=0);

  return buffer_[y*width_+x];
}

void Rasterizer::drawTriangle(const Triangle& tri) {
  Trapezoid traps[2];
  int traps_num=divide_into_trapezoids(tri, traps);

  for (int i=0;i<traps_num;++i) {
    const Trapezoid& t=traps[i];
    float lwidth=t.l.t.x-t.l.s.x;
    float rwidth=t.r.t.x-t.r.s.x;
    int top=static_cast<int>(t.t+0.5);
    int bottom=static_cast<int>(t.b+0.5);
    for (int y=top;y>=bottom;--y) {
      float k=(y-t.t)/(t.b-t.t);
      int lx=int(0.5+k*lwidth+t.l.s.x);
      int rx=int(0.5+k*rwidth+t.r.s.x);
      for (int x=lx;x<=rx;++x)
        setPixelAt(x, y, 0xFF);
    }
  }
}

void Rasterizer::draw( const Triangle& tri ) {
  Rect rect=Rect::make(static_cast<float>(height_), 0, 0, static_cast<float>(width_));
  std::vector<IntersectResult> results;
  if (!intersect(rect, tri, results))
    return;

  std::vector<Vec2> points=clip(results, tri, rect);
  const int triangle_num=points.size()/3;
  for (int i=0;i<triangle_num;++i) {
    Triangle new_triangle=Triangle::make(points[i*3],
                                         points[i*3+1],
                                         points[i*3+2]);
    drawTriangle(new_triangle);
  }
}

void Rasterizer::present() const {
  using std::cout;
  using std::endl;

  for (int y=height_-1;y>=0;--y) {
    for (int x=0;x<width_;++x) {
      if (0==buffer_[x+width_*y]) 
        cout<<"  ";
      else
        cout<<"* ";
    }
    cout<<endl;
  }
}

