//@date:2017.6.20
//@author:yangjie82@gmail.com
//@brief:demo for rendering with depth buffer
#pragma once
#include <memory>
#include "application.h"
//#include "camera.h"
#include "vec4.h"
class ArcBall;
class Camera;
class Device;
class PrimitiveStream;
class Texture;
struct MouseEventArgs;

class DemoDepthBuffer {
 public:
  explicit DemoDepthBuffer();
  virtual ~DemoDepthBuffer();
  virtual void run();
 
 private:
  Application app_;
  std::unique_ptr<Camera> camera_;
  Vec4 startRotation_;
  Vec4 deltaRotation_;
  bool isDragging_;
  std::unique_ptr<PrimitiveStream> stream_;
  std::unique_ptr<Texture> texture_;
  std::unique_ptr<ArcBall> arcball_;

  virtual void setup();
  virtual void teardown();
  // event handler
  virtual void onMouseEvent(MouseEventArgs& args);
  virtual void onFrameBeginEvent(Device& device);
};