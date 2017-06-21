#include "demodepthbuffer.h"
#include <iostream>
#include <iomanip>
#include "application.h"
#include "arcball.h"
#include "camera.h"
#include "color.h"
#include "device.h"
#include "matrix3x3.h"
#include "matrix4x4.h"
#include "mouseeventargs.h"
#include "primitivestream.h"
#include "quaternion.h"
#include "texture.h"
#include "triangle.h"
#include "triangle3d.h"
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"

DemoDepthBuffer::DemoDepthBuffer()
 : app_()
 , camera_(nullptr)
 , startRotation_(Vec4::kUnitW)
 , deltaRotation_(Vec4::kUnitW)
 , isDragging_(false)
 , stream_(nullptr)
 , texture_(nullptr)
 , arcball_(nullptr) {
  setup();
}

DemoDepthBuffer::~DemoDepthBuffer() {
  teardown();
}

void DemoDepthBuffer::setup() {
  // setup camera
  Camera::ViewParameters vp;
  vp.Eye    = Vec3::make(0.f,0.f,2.f);
  vp.Target = Vec3::make(0,0,-1);
  vp.Up     = Vec3::kUnitY;
  Camera::ProjectionParameters pp;
  pp.Aspect = 1.f;
  pp.Far    = 10.f;
  pp.Fov    = 3.1415926f/2.f;
  pp.Near   = 1.f;
  camera_.reset(new Camera(vp,pp));
  // setup primitive stream
  stream_.reset(new PrimitiveStream(PrimitiveType::TriangleList,2));
  Vec2 uvQuad[5]={
    Vec2::make(1,1),
    Vec2::make(0,1),
    Vec2::make(0,0),
    Vec2::make(1,0),
    Vec2::make(0.5f,0.5f),
  };
  Vec4 xyzwQuad[5]={
    Vec4::make(1,1,0,1),
    Vec4::make(-1,1,0,1),
    Vec4::make(-1,-1,0,1),
    Vec4::make(1,-1,0,1),
    Vec4::make(0,0,-1,1),
  };
  stream_->addVertex(xyzwQuad[0],std::valarray<f32>(uvQuad[0].m,2));
  stream_->addVertex(xyzwQuad[1],std::valarray<f32>(uvQuad[1].m,2));
  stream_->addVertex(xyzwQuad[2],std::valarray<f32>(uvQuad[2].m,2));
  stream_->addVertex(xyzwQuad[3],std::valarray<f32>(uvQuad[3].m,2));
  stream_->addVertex(xyzwQuad[4],std::valarray<f32>(uvQuad[4].m,2));
  stream_->addPrimitive(0,1,2);
  stream_->addPrimitive(0,2,3);
  stream_->addPrimitive(1,0,4);
  stream_->addPrimitive(2,1,4);
  stream_->addPrimitive(3,2,4);
  stream_->addPrimitive(0,3,4);
  // setup arcball
  const u32 width=512;
  const u32 height=512;
  arcball_.reset(new ArcBall(width,height));
  // load texture
  texture_.reset(new Texture("data/test.png"));
  texture_->generateMipmapChain();
  // setup app
  app_.setup(width,height);
  app_.setOnMouseEvent([this](MouseEventArgs& args) {
    this->onMouseEvent(args);
  });
  app_.setOnFrameBeginEvent([this](Device& device) {
    this->onFrameBeginEvent(device);
  });
}

void DemoDepthBuffer::run() {
  app_.run();
}

void DemoDepthBuffer::teardown() {
  app_.teardown();
}

void DemoDepthBuffer::onMouseEvent(MouseEventArgs& args) {
  char* name[5] = {
    "LeftButtonDown",
    "LeftButtonUp",
    "RightButtonDown",
    "RightButtonUp",
    "Move",
  };
  if (args.Type!=MouseEventArgs::Event::Move) {
    std::cout<<name[static_cast<int>(args.Type)]<<' : ';
    std::cout<<std::setw(8)<<args.X<<std::setw(8)<<args.Y<<std::endl;
  }
  switch (args.Type) {
  case MouseEventArgs::Event::LeftButtonDown:
    arcball_->beginDrag(args.X,args.Y);
    isDragging_=true;
    //deltaRotation_=arcball_->rotation();
    //app_.refresh();
    break;
  case MouseEventArgs::Event::LeftButtonUp:
    //arcball_->onDrag(args.X,args.Y);
    deltaRotation_=arcball_->rotation();
    arcball_->endDrag();
    isDragging_=false;
    startRotation_=deltaRotation_.quaternionMultiply(startRotation_);
    startRotation_=startRotation_.normalized();
    deltaRotation_=Vec4::kUnitW;
    app_.refresh();
    break;
  case MouseEventArgs::Event::Move:
    if (isDragging_) {
      arcball_->onDrag(args.X,args.Y);
      deltaRotation_=arcball_->rotation();
      app_.refresh();
    }
    break;
  }
}

void DemoDepthBuffer::onFrameBeginEvent(Device& device) {
  Matrix4x4 extra=Matrix4x4::makeRotation(
                    deltaRotation_.quaternionMultiply(startRotation_));
  camera_->setExtraMatrix(extra);    

  std::cout<<extra.determinant()<<std::endl;

  device.setCamera(*camera_);
  //device.setFramebuffer(fb);
  device.setPrimitiveStream(*stream_);
  device.setTexture(*texture_);

  device.clear();
  device.draw();
}