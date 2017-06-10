//@date:2016.9.1
//@author:yangjie82@gmail.com
//@brief:render device
#pragma once

class Triangle3D;
class Framebuffer;
class Camera;
class Rasterizer;
class Device {
 public:
  Device();
  virtual ~Device();
  virtual void setCamera(Camera& camera);
  virtual void setFramebuffer(Framebuffer& framebuffer);
  virtual void draw(const Triangle3D& shape);
  virtual void clear();
  virtual void present();

 private:
  Camera*      camera_;
  Framebuffer* framebuffer_;
  Rasterizer*  rasterizer_;
};