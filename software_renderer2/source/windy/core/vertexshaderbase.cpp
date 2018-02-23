#include "windy/core/vertexshaderbase.h"
#include "windy/core/inputvertex.h"

namespace windy {
VertexShaderBase::VertexShaderBase(const Matrix4x4& matrix_mvp) :
  matrixMVP_(matrix_mvp) 
{
}

VertexShaderBase::~VertexShaderBase()=default;

ShadedVertex VertexShaderBase::shade(const InputVertex& input_vertex) {
  auto vertexBase=static_cast<const ShadedVertex*>(input_vertex.vertex);
  return ShadedVertex {
    matrixMVP_*vertexBase->positionXYZW,
    vertexBase->uv0,
    vertexBase->uv1,
  };
}
}