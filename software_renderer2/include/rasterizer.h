//@date:2016.8.30
//@author:yangjie82@gmail.com
//@brief:simple rasterizer
#pragma once
#include <vector>
#include "base.h"
class DepthBuffer;
class FrameBuffer;
class PrimitiveStream;
class Triangle;
class Sampler;

class Rasterizer {
 public:
  Rasterizer(FrameBuffer& framebuffer,DepthBuffer& depthbuffer);
  ~Rasterizer();
  int width() const;
  int height() const;
  inline void setPixelAt(int x, int y, u32 color);
  void draw(const PrimitiveStream& stream,const Sampler& sampler);
 
 private:
  void drawTriangle(const Triangle& tri);
  void drawTriangle(u32                    primitiveIndex,
                    const PrimitiveStream& stream,
                    const Sampler&         sampler);
  int width_;
  int height_;
  //std::vector<int> buffer_;
  FrameBuffer* framebuffer_;
  DepthBuffer* depthbuffer_;

  Rasterizer(const Rasterizer& rhs);
  Rasterizer& operator=(const Rasterizer& rhs);
};