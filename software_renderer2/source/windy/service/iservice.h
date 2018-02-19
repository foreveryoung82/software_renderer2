//@date:2018.1.31
//@author:51790592@qq.com
//@brief:service interface for singleton which need to have deterministic life span
#pragma once
#include "windy/base/singleton.h"

namespace windy {
template <class _Ty>
class IService {
 public:
  static _Ty& instance() { return *instance_.get(); }
  static void initialize() { instance_=std::make_unique<_Ty>(); }
  static void finalize() { instance_.reset(); }

 protected:
  static std::unique_ptr<_Ty> instance_;
};
}

