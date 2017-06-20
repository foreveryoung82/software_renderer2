#include "rasterizer.h"
#include "rasterizer.inl"
#include <cassert>
#include <functional>
#include <memory>
#include "depthbuffer.h"
#include "framebuffer.h"
#include "interpolation.h"
#include "primitivestream.h"
#include "rect.h"
#include "sampler.h"
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

Rasterizer::Rasterizer(FrameBuffer& framebuffer,DepthBuffer& depthbuffer)
 : width_(framebuffer.width())
 , height_(framebuffer.height())
  //buffer_(width*height),
 , framebuffer_(&framebuffer)
 , depthbuffer_(&depthbuffer) {
}

Rasterizer::~Rasterizer() {
}

int Rasterizer::width() const {
  return width_;
}

int Rasterizer::height() const {
  return height_;
}

//void Rasterizer::setPixelAt( int x, int y, u32 color ) {
//  assert(x<width_ && x>=0);
//  assert(y<height_ && y>=0);
//
//  framebuffer_->setPixel(x,y,color);
//}

f32 get_x_by_y(const Vec2& s, const Vec2& t, f32 y) {
  return (y-t.y)*(s.x-t.x)/(s.y-t.y)+t.x;
}

f32 get_x_by_y(const Vec4& s, const Vec4& t, f32 y) {
  return (y-t.y)*(s.x-t.x)/(s.y-t.y)+t.x;
}

void Rasterizer::drawTriangle(u32   primitiveIndex,
                              const PrimitiveStream& stream,
                              const Sampler&         sampler) {
  auto v=[&stream](u32 idx){return stream.xyzwAt(idx);};
  auto a=[&stream](u32 idx){return stream.uvAt(idx);};
  IndexedTrapezoid traps[2];
  int traps_num=divide_into_trapezoids(primitiveIndex,stream,traps);
  PrimitiveStream::UV_t uv_l_div_w(stream.uvDimension());
  PrimitiveStream::UV_t uv_r_div_w(stream.uvDimension());
  PrimitiveStream::UV_t uv_div_w_step(stream.uvDimension());
  PrimitiveStream::UV_t uv_div_w(stream.uvDimension());
  PrimitiveStream::UV_t uv(stream.uvDimension());
  for (int i=0;i<traps_num;++i) {
    const IndexedTrapezoid& t=traps[i];
    const int top      = static_cast<int>(t.t);
    const float bottom = t.b;
    const Vec4& vl0=v(t.l[0]);
    const Vec4& vl1=v(t.l[1]);
    const Vec4& vr0=v(t.r[0]);
    const Vec4& vr1=v(t.r[1]);
    for (int y=top;y>=bottom;--y) {
      // remark(yangjie82@gmail.com): in some case, fl, fr may be negative,
      // use max to make program more robust
      f32 fl=std::max(0.f,(y-vl0.y)/(vl1.y-vl0.y));
      f32 fr=std::max(0.f,(y-vr0.y)/(vr1.y-vr0.y));
      f32 lw_inverse=lerp(vl0.w,vl1.w,fl);
      f32 rw_inverse=lerp(vr0.w,vr1.w,fr);
      int lx=static_cast<int>(0.5f+lerp(vl0.x,vl1.x,fl));
      int rx=static_cast<int>(0.5f+lerp(vr0.x,vr1.x,fr));
      lerp(a(t.l[0]),a(t.l[1]),fl,uv_l_div_w);
      lerp(a(t.r[0]),a(t.r[1]),fr,uv_r_div_w);
      // finite difference of uv_div_w
      uv_div_w=uv_l_div_w;
      uv_div_w_step=uv_r_div_w;
      uv_div_w_step-=uv_l_div_w;
      const f32 steps=static_cast<float>(rx-lx);
      uv_div_w_step*=1.f/steps;
      // finite difference of w_inverse
      f32 w_inverse=lw_inverse;
      f32 w_inverse_step=(rw_inverse-lw_inverse)*(1.f/steps);
      // fill scan line
      for (int x=lx;x<=rx;++x) {
        assert(0<=x && x<width_);
        const u32 c=sampler(uv_div_w[0]/w_inverse,
                            uv_div_w[1]/w_inverse).Value();
        setPixelAt(x,y,c);
        uv_div_w  += uv_div_w_step;
        w_inverse += w_inverse_step;
      }
    }
  }
}

void Rasterizer::draw(const PrimitiveStream& stream,const Sampler& sampler) {
  std::unique_ptr<PrimitiveStream> mapped(stream.clone());
  viewport_mapping(*mapped,width_,height_);
  int num=mapped->primitiveNum();
  for(int i=0;i<num;++i) {
    drawTriangle(i,*mapped,sampler);
  }
}
