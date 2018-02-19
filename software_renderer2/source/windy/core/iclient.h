//@date:2018.1.30
//@author:51790592@qq.com
//@brief:interface of client game
#pragma once
#include <memory>
namespace windy {
class IFramework;
struct FrameworkConfig;
struct EventFrame;
struct EventKey;
struct EventMouse; 
}

namespace windy {
class IClient {
 public:
  virtual ~IClient()=0;
  virtual const FrameworkConfig& config() const=0;
  virtual void onFrameEvent(const EventFrame& e)=0;
  virtual void onKeyEvent(const EventKey& e)=0;
  virtual void onMouseEvent(const EventMouse& e)=0;
};
}
