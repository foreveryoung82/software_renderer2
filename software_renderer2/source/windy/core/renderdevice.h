//@date:2018.2.20
//@author:51790592@qq.com
//@brief:software render device
#pragma once
#include <memory>
#include "windy/base/basetype.h"

namespace windy {
class IMainWindow;
class FrameBuffer;
}

namespace windy {
class RenderDevice {
 public:
  RenderDevice(IMainWindow& window,u32 frame_width,u32 frame_height);
  virtual ~RenderDevice();

  //virtual void drawTriangles();
  virtual void present();

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;;
};
}
