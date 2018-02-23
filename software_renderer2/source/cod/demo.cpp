#include "cod/demo.h"
#include "windy/core/eventframe.h"
#include "windy/core/inputvertexstream.h"
#include "windy/core/renderdevice.h"
#include "windy/core/shadedvertex.h"
#include "windy/math/matrix4x4.h"

using namespace windy;

namespace cod {
Demo::Demo() :
  config_(),
  vertices_(),
  inputStream_(nullptr),
  vertexShader_(Matrix4x4::makeIdentity())
{
  config_.width=640;
  config_.height=480;

  vertices_.reserve(3);
  vertices_.push_back(ShadedVertex{Vec4::make(-0.5f,0.5f,0.f,1.f),
                                   Vec2::kZero,
                                   Vec2::kZero});
  vertices_.push_back(ShadedVertex{Vec4::make(0.5f,0.8f,0.f,1.f),
                                   Vec2::kZero,
                                   Vec2::kZero});
  vertices_.push_back(ShadedVertex{Vec4::make(0.f,-0.5f,0.f,1.f),
                                   Vec2::kZero,
                                   Vec2::kZero});
  inputStream_.reset(new InputVertexStream(vertices_.data(),
                                           3,// vertices num
                                           sizeof(ShadedVertex)));
}

Demo::~Demo() {
}

const windy::FrameworkConfig& Demo::config() const {
  return config_;
}

void Demo::onFrameEvent(const windy::EventFrame& e) {
  RenderDevice* device=e.renderDevice;
  device->setVertexShader(vertexShader_);
  device->drawTriangles(*inputStream_,1);
}

void Demo::onKeyEvent(const windy::EventKey& e) {
}

void Demo::onMouseEvent(const windy::EventMouse& e) {
}
}