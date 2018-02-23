//@date:2018.2.22
//@author:51790592@qq.com
//@brief:software rasterizer
#pragma once
#include "windy/base/basetype.h"

namespace windy {
struct ShadedVertex;
class FrameBuffer;
}

namespace windy {
class Rasterizer {
 public:
  void drawTriangle(const ShadedVertex* vertices,
                    u32 triangle_num,
                    FrameBuffer& frame_buffer) const;

 private:
  void drawBresenham_(i32 sx,
                      i32 sy,
                      i32 tx,
                      i32 ty,
                      FrameBuffer& frame_buffer) const;
};
}