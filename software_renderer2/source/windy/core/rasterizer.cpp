#include <algorithm>
#include "windy/core/rasterizer.h"
#include "windy/core/shadedvertex.h"
#include "windy/core/framebuffer.h"

namespace {
template <class type_draw_func>
void drawBresenham(windy::i32 sx,
                   windy::i32 sy,
                   windy::i32 tx,
                   windy::i32 ty,
                   type_draw_func draw_func ) {
  windy::i32 w=tx-sx;
  windy::i32 h=ty-sy;

  windy::i32 f=2*h-w;
  windy::i32 x=sx;
  windy::i32 y=sy;

  draw_func(sx,sy);
  while (x<tx) {
    ++x;
    if (f>0) {
      f+=2*(h-w);
      y++;
    }
    else {
      f+=2*h;
    }
    draw_func(x,y);
  }  
}
}

namespace windy {
void Rasterizer::drawTriangle(const ShadedVertex* vertices, 
                              u32 triangle_num,
                              FrameBuffer& frame_buffer) const {
  const f32 frameWidthOver2=0.5f*frame_buffer.width();
  const f32 frameHeighOver2t=0.5f*frame_buffer.height();

  for (u32 triangleIndex=0;triangleIndex<triangle_num;++triangleIndex) {
    for (u32 pointIndex=0;pointIndex<3;++pointIndex) {
      const auto& s=vertices[triangleIndex*3+pointIndex];
      const auto& t=vertices[triangleIndex*3+(pointIndex+1)%3];
      const i32 sx=static_cast<i32>((s.positionXYZW.x+1.f)*frameWidthOver2);
      const i32 sy=static_cast<i32>((s.positionXYZW.y+1.f)*frameHeighOver2t);
      const i32 tx=static_cast<i32>((t.positionXYZW.x+1.f)*frameWidthOver2);
      const i32 ty=static_cast<i32>((t.positionXYZW.y+1.f)*frameHeighOver2t);
      drawBresenham_(sx,sy,tx,ty,frame_buffer);
    }
  }
}
void Rasterizer::drawBresenham_(i32 sx,
                                i32 sy,
                                i32 tx,
                                i32 ty,
                                FrameBuffer& frame_buffer) const {
  const Color c={0xff,0xff,0xff,0xff};
  i32 w=tx-sx;
  i32 h=ty-sy;
  bool isStepByX=(std::abs(w) >= std::abs(h));
  if (w>=0) {
    if (h>=0) {
      if (isStepByX) {
        drawBresenham(sx,
                      sy,
                      tx,
                      ty,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(x,y,c);
                      });
      } else {
        drawBresenham(sy,
                      sx,
                      ty,
                      tx,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(y,x,c);
                      });
      }
    } else {
      if (isStepByX) {
        drawBresenham(sx,
                      -sy,
                      tx,
                      -ty,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(x,-y,c);
                      });
      } else {
        drawBresenham(-sy,
                      sx,
                      -ty,
                      tx,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(y,-x,c);
                      });
      }
    }
  } else {
    if (h>=0) {
      if (isStepByX) {
        drawBresenham(-sx,
                      sy,
                      -tx,
                      ty,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(-x,y,c);
                      });
      } else {
        drawBresenham(sy,
                      -sx,
                      ty,
                      -tx,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(-y,x,c);
                      });
      }
    } else {
      if (isStepByX) {
        drawBresenham(-sx,
                      -sy,
                      -tx,
                      -ty,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(-x,-y,c);
                      });
      } else {
        drawBresenham(-sy,
                      -sx,
                      -ty,
                      -tx,
                      [&frame_buffer,&c](i32 x,i32 y){
                        frame_buffer.setPixel(-y,-x,c);
                      });    
      }
    }
  }
  //i32 f=2*h-w;
  //i32 x=sx;
  //i32 y=sy;

  //frame_buffer.setPixel(sx,sy,c);
  //while (x<tx) {
  //  ++x;
  //  if (f>0) {
  //    f+=2*(h-w);
  //    y++;
  //  }
  //  else {
  //    f+=2*h;
  //  }
  //  frame_buffer.setPixel(x,y,c);
  //}
}
}
