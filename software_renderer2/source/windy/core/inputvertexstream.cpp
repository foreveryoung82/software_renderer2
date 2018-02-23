#include "windy/core/inputvertexstream.h"

namespace windy {
InputVertexStream::InputVertexStream(const void* buffer,
                                     u32 vertex_num,
                                     u32 vertex_bytes) :
  buffer_(buffer),
  vertexNum_(vertex_num),
  vertexBytes_(vertex_bytes) 
{
}
  
InputVertex InputVertexStream::vertexAt(u32 index) const {
  const u32 offset = index*vertexBytes_;
  const void* ptr  = static_cast<const u8*>(buffer_)+offset;
  return InputVertex {ptr};
}
}