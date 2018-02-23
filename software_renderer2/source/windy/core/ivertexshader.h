//@date:2018.2.22
//@author:51790592@qq.com
//@brief:interface for vertex shader
#pragma once
#include "windy/core/shadedvertex.h"
namespace windy {
struct InputVertex;
}

namespace windy {
class IVertexShader {
 public:
  virtual ~IVertexShader()=0;

  virtual ShadedVertex shade(const InputVertex& input_vertex)=0; 
};
}
