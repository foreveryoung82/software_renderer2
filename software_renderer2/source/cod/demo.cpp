#include "cod/demo.h"

namespace cod {
Demo::Demo()
{
  config_.width=640;
  config_.height=480;
}

Demo::~Demo() {
}

const windy::FrameworkConfig& Demo::config() const {
  return config_;
}

void Demo::onFrameEvent(const windy::EventFrame& e) {
}

void Demo::onKeyEvent(const windy::EventKey& e) {
}

void Demo::onMouseEvent(const windy::EventMouse& e) {
}
}