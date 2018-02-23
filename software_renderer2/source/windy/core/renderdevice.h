//@date:2018.2.20
//@author:51790592@qq.com
//@brief:software render device
#pragma once
#include <memory>
#include "windy/base/basetype.h"

namespace windy {
class IMainWindow;
class FrameBuffer;
class InputVertexStream;
class IVertexShader;
}

namespace windy {
class RenderDevice {
 public:
  RenderDevice(IMainWindow& window,u32 frame_width,u32 frame_height);
  virtual ~RenderDevice();

  virtual void setVertexShader(IVertexShader& vertex_shader);
  virtual void drawTriangles(const InputVertexStream& input_stream,
                             u32 triangles_num);
  virtual void present();

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;;
};
}
