//@date:2018.1.30
//@author:51790592@qq.com
//@brief:collision detection demo
#pragma once
#include "windy/core/iclient.h"
#include "windy/core/frameworkconfig.h"

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
  windy::FrameworkConfig config_;
};
}
