//@date:2018.1.31
//@author:51790592@qq.com
//@brief:high precision system timer
#pragma once
#include "windy/base/basetype.h"
#include "windy/service/iservice.h"
namespace windy {
class ServiceTime:public IService<ServiceTime> {
 public:
  enum TimerID:u8 {
    Client=0,
  };

  ServiceTime();
  ~ServiceTime();

  void startTimer(u8 timer_id);
  void tickTimer(u8 timer_id);
  f32 totalSeconds(u8 timer_id) const;
  f32 deltaSeconds(u8 timer_id) const;
  void sleep(f32 seconds);
  
 private:
  i64 startTime_;
  i64 nowTime_;
  i64 prevTime_;
  i64 countPerSecond_;
};
}
