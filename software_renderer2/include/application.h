//@date:2016.9.2
//@author:yangjie82@gmail.com
//@brief:platform specific application base class
#pragma once
#include <functional>
struct ApplicationImpl;
class Framebuffer;
struct MouseEventArgs;

class Application {
 public:
  typedef std::function<void(Framebuffer& framebuffer)> onFrameBeginEvent_t;
  typedef std::function<void(MouseEventArgs& args)> onMouseEvent_t;
  Application();
  virtual ~Application();
  virtual void setup(int width, int height);
  virtual void teardown();
  virtual void run();
  virtual void refresh(); // call when frame begin event needed
  virtual void setOnFrameBeginEvent(onFrameBeginEvent_t onFrameBeginEvent);
  virtual void setOnMouseEvent(onMouseEvent_t onMouseEvent);

  // remark(jieyang@gmail.com):following methods are only for win32 msg handler
  // users should not call them directly!
  virtual void fireOnFrameBeginEvent();
  virtual void fireOnMouseEvent(MouseEventArgs& args);

private:
  int width_;
  int height_;
  ApplicationImpl*    impl_;
  Framebuffer*        framebuffer_;
  onFrameBeginEvent_t onFrameBeginEvent_;
  onMouseEvent_t      onMouseEvent_;
};