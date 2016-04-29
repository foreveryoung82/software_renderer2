#pragma once
#include <cstdint>
#include "line2.h"

struct IntersectResult {
  enum: std::uint8_t {
    kInvalidRectEdgeIdx=0xFF,
  };
  Line2 line;
  std::uint8_t rectBoundIdx[2];
  bool isIntersected;
};