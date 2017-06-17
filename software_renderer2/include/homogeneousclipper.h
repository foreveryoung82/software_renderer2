//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:clip triangle by view frustum in homogeneous space
#pragma once
#include <vector>
#include <valarray>
#include "vec4.h"
class Triangle3D;
class PrimitiveStream;

class HomogeneousClipper {
 public:
   //static std::vector<Vec4> clipWithInfinitesimalW(Vec4 const& v0,
   //                                                Vec4 const& v1,
   //                                                Vec4 const& v2);
   //static std::vector<Vec4> clipWithcanonicalViewVolume(Vec4 const& v0,
   //                                                     Vec4 const& v1,
   //                                                     Vec4 const& v2);
   //static int clipWithInfinitesimalW(
   //  int idx0,
   //  int idx1,
   //  int idx2,
   //  const std::vector<Vec4>&                inXYZW,
   //  const std::vector<std::valarray<f32>*>& inUV,
   //  std::vector<Vec4>&                      outXYZW,
   //  std::vector<std::valarray<f32>*>&       outUV);

   //static int clipWithcanonicalViewVolume(
   //  int idx0,
   //  int idx1,
   //  int idx2,
   //  const std::vector<Vec4>&                inXYZW,
   //  const std::vector<std::valarray<f32>*>& inUV,
   //  std::vector<Vec4>&                      outXYZW,
   //  std::vector<std::valarray<f32>*>&       outUV);

   static int clipWithInfinitesimalW(u32                    primitiveIndex,
                                     const PrimitiveStream& inStream,
                                     PrimitiveStream&       outStream);
   static int clipWithInfinitesimalW(const PrimitiveStream& inStream,
                                     PrimitiveStream&       outStream);

   static int clipWithcanonicalViewVolume(u32                    primitiveIndex,
                                          const PrimitiveStream& inStream,
                                          PrimitiveStream&       outStream);
   static int clipWithcanonicalViewVolume(const PrimitiveStream& inStream,
                                          PrimitiveStream&       outStream);
};