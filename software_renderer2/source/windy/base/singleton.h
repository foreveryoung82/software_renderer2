//@date:2018.1.30
//@author:51790592@qq.com
//@brief:singleton template class
#pragma once
#include <memory>

namespace windy {
template <class _Ty>
class Singleton {
 public:
  static _Ty& instance() {
    _Ty::initializeIfNotYet();
    return *instance_.get();
  }

 protected:
  static std::unique_ptr<_Ty> instance_;
};
}
