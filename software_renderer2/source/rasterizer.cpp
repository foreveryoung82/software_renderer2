#include "rasterizer.h"
#include <cassert>
#include <functional>
#include <memory>
#include "framebuffer.h"
#include "interpolation.h"
#include "primitivestream.h"
#include "rect.h"
#include "trapezoid.h"
#include "triangle.h"

namespace {
void viewport_mapping(PrimitiveStream& stream,int width,int height) {
  const int vertNum=stream.vertexNum();
  for (int i=0;i<vertNum;++i) {
    Vec4& xyzw=stream.xyzwAt(i);
    xyzw.x=(xyzw.x+1.f)*0.5f*(width-1);
    xyzw.y=(xyzw.y+1.f)*0.5f*(height-1);
  }
}
}

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

f32 get_x_by_y(const Vec2& s, const Vec2& t, f32 y) {
  return (y-t.y)*(s.x-t.x)/(s.y-t.y)+t.x;
}

f32 get_x_by_y(const Vec4& s, const Vec4& t, f32 y) {
  return (y-t.y)*(s.x-t.x)/(s.y-t.y)+t.x;
}

void Rasterizer::drawTriangle(const Triangle& tri) {
  Trapezoid traps[2];
  int traps_num=divide_into_trapezoids(tri, traps);

  for (int i=0;i<traps_num;++i) {
    const Trapezoid& t=traps[i];
    const float top=t.t;
    const float bottom=t.b;
    for (int y=static_cast<int>(top);y>=bottom;--y) {
      int lx=static_cast<int>(0.5f+get_x_by_y(t.l.s, t.l.t,static_cast<f32>(y)));
      int rx=static_cast<int>(0.5f+get_x_by_y(t.r.s, t.r.t,static_cast<f32>(y)));
      for (int x=lx;x<=rx;++x)
        if (x>=0 && x<width_)
          setPixelAt(x, y, 0xff);
    }
  }
}

void Rasterizer::drawTriangle(u32   primitiveIndex,
                              const PrimitiveStream& stream) {
  auto v=[&stream](u32 idx){return stream.xyzwAt(idx);};
  auto a=[&stream](u32 idx){return stream.uvAt(idx);};
  IndexedTrapezoid traps[2];
  int traps_num=divide_into_trapezoids(primitiveIndex,stream,traps);
  PrimitiveStream::UV_t uv_l(stream.uvDimension());
  PrimitiveStream::UV_t uv_r(stream.uvDimension());
  PrimitiveStream::UV_t uv(stream.uvDimension());
  for (int i=0;i<traps_num;++i) {
    const IndexedTrapezoid& t=traps[i];
    const int top    = static_cast<int>(t.t);
    const float bottom = t.b;
    for (int y=top;y>=bottom;--y) {
      f32 fl=(y-v(t.l[0]).y)/(v(t.l[1]).y-v(t.l[0]).y);
      f32 fr=(y-v(t.r[0]).y)/(v(t.r[1]).y-v(t.r[0]).y);
      int lx=static_cast<int>(0.5f+lerp(v(t.l[0]).x,v(t.l[1]).x,fl));
      int rx=static_cast<int>(0.5f+lerp(v(t.r[0]).x,v(t.r[1]).x,fr));
      uv_l=lerp(a(t.l[0]),a(t.l[1]),fl);
      uv_r=lerp(a(t.r[0]),a(t.r[1]),fr);
      for (int x=lx;x<=rx;++x) {
        if (x<0 || x>width_)
          continue;
        f32 f=static_cast<f32>(x-lx)/(rx-lx);
        uv=lerp(uv_l,uv_r,f);
        setPixelAt(x, y, 0xff<<24|
                         static_cast<u32>(uv[0]*256)<<16|
                         static_cast<u32>(uv[1]*256)<<8 |
                         static_cast<u32>(uv[2]*256));
      }
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

void Rasterizer::draw(const PrimitiveStream& stream) {
  std::unique_ptr<PrimitiveStream> mapped(stream.clone());
  viewport_mapping(*mapped,width_,height_);
  int num=mapped->primitiveNum();
  for(int i=0;i<num;++i) {
    drawTriangle(i,*mapped);
  }
}
