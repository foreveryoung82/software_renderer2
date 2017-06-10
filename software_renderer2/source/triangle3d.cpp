#include "triangle3d.h"

Triangle3D Triangle3D::make(Vec3 const& p0, Vec3 const& p1, Vec3 const& p2) {
  Triangle3D ret;
  ret.p0=p0;
  ret.p1=p1;
  ret.p2=p2;
  return ret;
}

