//@date:2018.1.30
//@author:51790592@qq.com
//@brief:interface of client framework
#pragma once
//#include <memory>
#include <functional>
namespace windy {
class IMainWindow;
class IClient;
}

namespace windy {
class IFramework {
 public:
  typedef std::function<void()> finalizer_t;

  virtual ~IFramework()=0;
  virtual IMainWindow& mainWindow() const=0;
  virtual void run(IClient& client)=0;
  virtual void registerFinalizer(finalizer_t finalizer)=0;
};
}

// remark(51790592@qq.com):get global framework instance.
// you must implement following function yourself
namespace windy {
IFramework& GetFrameworkInstance();
}