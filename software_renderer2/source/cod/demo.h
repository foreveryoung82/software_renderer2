//@date:2018.1.30
//@author:51790592@qq.com
//@brief:collision detection demo
#pragma once
#include <memory>
#include <vector>
#include "windy/core/iclient.h"
#include "windy/core/frameworkconfig.h"
#include "windy/core/shadedvertex.h"
#include "windy/core/vertexshaderbase.h"

namespace windy {
class InputVertexStream;
}

namespace cod {
class Demo:public windy::IClient {
 public:
  Demo();
  virtual ~Demo();
  virtual const windy::FrameworkConfig& config() const override;
  virtual void onFrameEvent(const windy::EventFrame& e) override;
  virtual void onKeyEvent(const windy::EventKey& e) override;
  virtual void onMouseEvent(const windy::EventMouse& e) override;

 private:
  windy::FrameworkConfig                    config_;
  std::vector<windy::ShadedVertex>          vertices_;
  std::unique_ptr<windy::InputVertexStream> inputStream_;
  windy::VertexShaderBase                   vertexShader_;
};
}
