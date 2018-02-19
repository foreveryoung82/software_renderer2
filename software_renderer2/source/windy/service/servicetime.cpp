#include "windy/service/serviceTime.h"
#include <cassert>
#include <windows.h>

namespace windy {
std::unique_ptr<ServiceTime> ServiceTime::instance_=nullptr;

ServiceTime::ServiceTime()
 : startTime_(0)
 , nowTime_(0)
 , prevTime_(0)
 , countPerSecond_(0) {
  LARGE_INTEGER ticks;
  QueryPerformanceFrequency(&ticks);
  countPerSecond_ = ticks.QuadPart;
}

ServiceTime::~ServiceTime() {
}

void ServiceTime::startTimer(u8 timer_id) {
  assert(TimerID::Client==timer_id);

  LARGE_INTEGER ticks;
  QueryPerformanceCounter(&ticks);
  startTime_ = ticks.QuadPart;
  nowTime_   = startTime_;
  prevTime_  = startTime_;
}

void ServiceTime::tickTimer(u8 timer_id) {
  LARGE_INTEGER ticks;
  QueryPerformanceCounter(&ticks);
  prevTime_=nowTime_;
  nowTime_=ticks.QuadPart;
}

f32 ServiceTime::totalSeconds(u8 timer_id) const {
  assert(TimerID::Client==timer_id);

  auto total_seconds=
    static_cast<double>(nowTime_)/static_cast<double>(countPerSecond_);
  return static_cast<f32>(total_seconds);
}

f32 ServiceTime::deltaSeconds(u8 timer_id) const {
  assert(TimerID::Client==timer_id);

  auto delta_ticks   = nowTime_-prevTime_;
  auto delta_seconds = 
    static_cast<double>(delta_ticks)/static_cast<double>(countPerSecond_);
  return static_cast<f32>(delta_seconds);
}

void ServiceTime::sleep(f32 seconds) {
  Sleep(static_cast<u32>(seconds*1000));
}
}
