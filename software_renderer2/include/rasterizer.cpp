#include "rasterizer.h"
#include <cassert>
#include "rect.h"
#include "trapezoid.h"
#include "triangle.h"
#include "framebuffer.h"

Rasterizer::Rasterizer(Framebuffer& framebuffer)
 :width_(framebuffer.width()),
  height_(framebuffer.height()),
  //buffer_(width*height),
  framebuffer_(&framebuffer) {
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

  framebuffer_->setPixel(x,y,color);
}

float get_x_by_y(const Vec2& s, const Vec2& t, float y) {
  return (y-t.y)*(s.x-t.x)/(s.y-t.y)+t.x;
}

void Rasterizer::drawTriangle(const Triangle& tri) {
  Trapezoid traps[2];
  int traps_num=divide_into_trapezoids(tri, traps);

  for (int i=0;i<traps_num;++i) {
    const Trapezoid& t=traps[i];
    //float lwidth=t.l.s.x-t.l.t.x;
    //float rwidth=t.r.s.x-t.r.t.x;
    int top=static_cast<int>(t.t+0.5);
    int bottom=static_cast<int>(t.b+0.5);
    for (int y=top;y>=bottom;--y) {
      //float k=(y-t.b)/(t.t-t.b);
      int lx=static_cast<int>(0.5f+get_x_by_y(t.l.s, t.l.t,static_cast<float>(y)));
      int rx=static_cast<int>(0.5f+get_x_by_y(t.r.s, t.r.t,static_cast<float>(y)));
      for (int x=lx;x<=rx;++x)
        if (x>=0 && x<width_)
          setPixelAt(x, y, 0xFF);
    }
  }
}

void Rasterizer::draw( const Triangle& tri ) {
  Triangle ret;
  for (int i=0;i<3;++i) {
    ret.m[i].x=(tri.m[i].x+1)*0.5f*(width_-1);
    ret.m[i].y=(tri.m[i].y+1)*0.5f*(height_-1);
  }
  drawTriangle(ret);
}
