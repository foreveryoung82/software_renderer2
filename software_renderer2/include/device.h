//@date:2016.9.1
//@author:yangjie82@gmail.com
//@brief:render device
#pragma once

class Triangle;
class Framebuffer;
class Rasterizer;
class Device {
 public:
  Device();
  virtual ~Device();
  virtual void setFramebuffer(Framebuffer& framebuffer);
  virtual void draw(const Triangle& shape);
  virtual void clear();
  virtual void present();

 private:
  Framebuffer* framebuffer_;
  Rasterizer* rasterizer_;
};