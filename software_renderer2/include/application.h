//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:platform specific application base class
#pragma once
#include <functional>

struct ApplicationImpl;
class FrameBuffer;
class Application {
 public:
  typedef std::function<void(FrameBuffer& framebuffer)> onFrameBeginEvent_t;
  Application();
  virtual ~Application();
  virtual void setup(int width, int height);
  virtual void teardown();
  virtual void run();
  virtual void setOnFrameBeginEvent(onFrameBeginEvent_t onFrameBeginEvent);
  virtual void fireOnFrameBeginEvent(); // this should be called by user!

private:
  int width_;
  int height_;
  ApplicationImpl*    impl_;
  onFrameBeginEvent_t onFrameBeginEvent_;
};