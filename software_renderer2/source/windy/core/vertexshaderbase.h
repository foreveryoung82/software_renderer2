//@date:2018.2.22
//@author:51790592@qq.com
//@brief:basic vertex shader
#pragma once
#include "windy/core/ivertexshader.h"
#include "windy/math/matrix4x4.h"

namespace windy {
class VertexShaderBase : public IVertexShader {
 public:
  explicit VertexShaderBase(const Matrix4x4& matrix_mvp);
  virtual ~VertexShaderBase();

  virtual ShadedVertex shade(const InputVertex& input_vertex) override;

 private:
  Matrix4x4 matrixMVP_;
};
}