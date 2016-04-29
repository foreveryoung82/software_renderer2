#include "partition.h"
#include <cmath>
#include <limits>
#include "line2.h"
#include "vec2.h"
using namespace std;

PartitionResult partition(Line2 const& line, Vec2 const& point) {
  return partition(line,point,numeric_limits<float>::epsilon());
}

PartitionResult partition(Line2 const& line, Vec2 const& point, float epsilon) {
  float d=line.normal().dot(point-line.s);
  if (d<-epsilon)
    return PartitionResult::kRight;
  else if (d>epsilon)
    return PartitionResult::kLeft;
  else
    return PartitionResult::kOnLine;
}
