//@date:2016.9.1
//@author:yangjie82@gmail.com
//@brief:render device
#pragma once
#include "base.h"
class Camera;
class DepthBuffer;
class FrameBuffer;
class PrimitiveStream;
class Rasterizer;
class Texture;
class Triangle3D;

class Device {
 public:
  Device(void* bytes,u32 width,u32 height);
  virtual ~Device();
  virtual void setCamera(Camera& camera);
  //virtual void setFramebuffer(FrameBuffer& framebuffer);
  virtual void setDepthbuffer(DepthBuffer& framebuffer);
  virtual void setPrimitiveStream(const PrimitiveStream& primitiveStream);
  virtual void setTexture(Texture& texture);
  virtual void draw();
  virtual void blit(const Texture& tex);
  virtual void clear();
  virtual void present();

 private:
  u32                    width_;
  u32                    height_;
  Camera*                camera_;
  FrameBuffer*           framebuffer_;
  DepthBuffer*           depthbuffer_;
  const PrimitiveStream* primitiveStream_;
  Texture*               texture_;
  Rasterizer*            rasterizer_;
};