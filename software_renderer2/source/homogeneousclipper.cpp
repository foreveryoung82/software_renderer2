#include "homogeneousclipper.h"
#include <cassert>
#include <algorithm>
#include <iterator>
#include <valarray>
#include <array>
#include "triangle3d.h"
//#include "valarrayext.h"
#include "interpolation.h"
#include "primitivestream.h"

namespace {
  f32 compute_boundary_condition(Vec4 const& v,int axis,int sign) {
    return (v[3]-sign*v[axis]);
  }

void homogeneous_clip_view_unit_plane(
  int axis,
  int sign,
  const std::vector<Vec4>&                inXYZW,
  const std::vector<std::valarray<f32>>&  inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>>&        outUV) {

  const int vertsNum=inXYZW.size();
  for(int i=0;i<vertsNum;++i) {
    const int prev=(i+vertsNum-1)%vertsNum;
    const f32 prevBC=compute_boundary_condition(inXYZW[prev],axis,sign);
    const f32 currBC=compute_boundary_condition(inXYZW[i],axis,sign);
    if (0 > prevBC*currBC) {
      f32 tHit=currBC/(currBC-prevBC);
      outXYZW.push_back(lerp(inXYZW[i],inXYZW[prev],tHit));
      outUV.push_back(lerp(inUV[i],inUV[prev],tHit));
    }
    if (0 <= currBC) {
      outXYZW.push_back(inXYZW[i]);
      outUV.push_back(inUV[i]);
    }
  }
}
}

int HomogeneousClipper::clipWithInfinitesimalW(
  u32                    primitiveIndex,
  const PrimitiveStream& inStream,
  PrimitiveStream&       outStream) {
  assert(PrimitiveType::TriangleList==inStream.primitiveType());

  const f32 w=0.00001f;
  const u32 idxStartIndex=primitiveIndex*3;
  const u32 idx0=inStream.indexAt(idxStartIndex);
  const u32 idx1=inStream.indexAt(idxStartIndex+1);
  const u32 idx2=inStream.indexAt(idxStartIndex+2);
  const Vec4* xyzw[3]={
    &inStream.xyzwAt(idx0),
    &inStream.xyzwAt(idx1),
    &inStream.xyzwAt(idx2),
  };
  const std::valarray<f32>* uv[3]={
    &inStream.uvAt(idx0),
    &inStream.uvAt(idx1),
    &inStream.uvAt(idx2),
  };
  const bool isIn[3]={
    xyzw[0]->w > w,
    xyzw[1]->w > w,
    xyzw[2]->w > w
  };
  const u32 vertNumBeforeClip=outStream.vertexNum();
  for(int i=0;i<3;++i) {
    int prev=(i+2)%3;
    if(isIn[prev] != isIn[i]) {
      const f32 t = (xyzw[i]->w - w)/(xyzw[i]->w - xyzw[prev]->w);
      const Vec4 hitXYZW=lerp(*xyzw[i],*xyzw[prev],t);
      const std::valarray<f32> hitUV=lerp(*uv[i],*uv[prev],t);
      outStream.addVertex(hitXYZW,hitUV);
    }
    if(isIn[i]) {
      outStream.addVertex(*xyzw[i],*uv[i]);
    }
  }
  const int primitiveNum=outStream.vertexNum()-vertNumBeforeClip-2;
  if (0>=primitiveNum)
    return 0;
  const int indexBase=vertNumBeforeClip;
  for(int i=0;i<primitiveNum;++i) {
    outStream.addPrimitive(indexBase, indexBase+i+1, indexBase+i+2);
  }
  return primitiveNum;
}

int HomogeneousClipper::clipWithInfinitesimalW(
  const PrimitiveStream& inStream,
  PrimitiveStream&       outStream) {
  const int primitiveNumBeforeClip=inStream.primitiveNum();
  int newPrimitiveNum=0;
  for(int i=0;i<primitiveNumBeforeClip;++i) {
    newPrimitiveNum+=clipWithInfinitesimalW(i,inStream,outStream);
  }
  return newPrimitiveNum;
}

int HomogeneousClipper::clipWithcanonicalViewVolume(
  u32                    primitiveIndex,
  const PrimitiveStream& inStream,
  PrimitiveStream&       outStream) {
  assert(PrimitiveType::TriangleList==inStream.primitiveType());

  const u32 idxStartIndex=primitiveIndex*3;
  const u32 idx0=inStream.indexAt(idxStartIndex);
  const u32 idx1=inStream.indexAt(idxStartIndex+1);
  const u32 idx2=inStream.indexAt(idxStartIndex+2);
  PrimitiveStream::XYZWVec_t inXYZW;
  inXYZW.push_back(inStream.xyzwAt(idx0));
  inXYZW.push_back(inStream.xyzwAt(idx1));
  inXYZW.push_back(inStream.xyzwAt(idx2));
  PrimitiveStream::UVVec_t   inUV;
  inUV.push_back(inStream.uvAt(idx0));
  inUV.push_back(inStream.uvAt(idx1));
  inUV.push_back(inStream.uvAt(idx2));
  
  PrimitiveStream::XYZWVec_t outXYZW;
  PrimitiveStream::UVVec_t   outUV;

  for(int axis=0;axis<3;++axis) {
    for(int sign=-1;sign<=1;sign+=2) {
      homogeneous_clip_view_unit_plane(axis,sign,inXYZW,inUV,outXYZW,outUV);
      inXYZW.clear();
      inXYZW.swap(outXYZW);
      inUV.clear();
      inUV.swap(outUV);
    }
  }
  if (0==inXYZW.size())
    return 0;
  const int vertNum=inXYZW.size();
  const int baseIndex=outStream.vertexNum();
  for(int i=0;i<vertNum;++i) {
    outStream.addVertex(inXYZW[i],inUV[i]);
  }
  const int newPrimitiveNum=inXYZW.size()-2;
  for(int i=0;i<newPrimitiveNum;++i) {
    outStream.addPrimitive(baseIndex,baseIndex+i+1,baseIndex+i+2);
  }
  return newPrimitiveNum;
}

int HomogeneousClipper::clipWithcanonicalViewVolume(
  const PrimitiveStream& inStream,
  PrimitiveStream&       outStream) {
  const int primitiveNumBeforeClip=inStream.primitiveNum();
  int newPrimitiveNum=0;
  for(int i=0;i<primitiveNumBeforeClip;++i) {
    newPrimitiveNum+=clipWithcanonicalViewVolume(i,inStream,outStream);
  }
  return newPrimitiveNum;  
}