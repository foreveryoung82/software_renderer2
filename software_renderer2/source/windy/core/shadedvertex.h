//@date:2018.2.22
//@author:51790592@qq.com
//@brief:shaded vertex
#pragma once
#include "windy/math/vec2.h"
#include "windy/math/vec4.h"

namespace windy {
struct ShadedVertex {
  Vec4 positionXYZW;
  Vec2 uv0;
  Vec2 uv1;
};
}