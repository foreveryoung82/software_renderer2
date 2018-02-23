#include "windy/core/framebuffer.h"
#include <algorithm>

namespace windy {
FrameBuffer::FrameBuffer(u32* raw_pixels,u32 width,u32 height,u32 stride)
 : rawPixels_(raw_pixels)
 , width_(width)
 , height_(height)
 , stride_(stride) {
}

FrameBuffer::~FrameBuffer() {
}

void FrameBuffer::clear(Color color) {
  std::fill_n(rawPixels_, height_*stride_/4, color.value());
}
}