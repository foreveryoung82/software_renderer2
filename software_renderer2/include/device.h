//@date:2016.9.1
//@author:yangjie82@gmail.com
//@brief:render device
#pragma once
#include "deviceparameters.h"

class Triangle;
struct DevicePlatform;
class Device {
 public:
  Device(const DeviceParameters& param);
  virtual ~Device();
  virtual void draw(const Triangle& shape);
  virtual void clear();
  virtual void present();

 private:
  DeviceParameters param_;
  DevicePlatform*  platform_;
};