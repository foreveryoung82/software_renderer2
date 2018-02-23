//@date:2018.2.22
//@author:51790592@qq.com
//@brief:input vertex stream
#pragma once
#include "windy/base/basetype.h"
#include "windy/core/inputvertex.h"

namespace windy {
class InputVertexStream {
 public :
  InputVertexStream(const void* buffer,u32 vertex_num,u32 vertex_bytes);
  
  InputVertex vertexAt(u32 index) const;

 private:
  const void* buffer_;
  const u32 vertexNum_;
  const u32 vertexBytes_;
};
}