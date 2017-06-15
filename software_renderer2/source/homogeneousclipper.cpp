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
  const std::vector<std::valarray<f32>*>& inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>*>&       outUV) {

  const int vertsNum=inXYZW.size();
  for(int i=0;i<vertsNum;++i) {
    const int prev=(i+vertsNum-1)%vertsNum;
    const Vec4 prevXYZW=inXYZW[prev];
    const Vec4 currXYZW=inXYZW[i];
    const std::valarray<f32>& prevUV=*inUV[prev];
    const std::valarray<f32>& currUV=*inUV[i];
    const f32 prevBC=compute_boundary_condition(prevXYZW,axis,sign);
    const f32 currBC=compute_boundary_condition(currXYZW,axis,sign);
    if (0 > prevBC*currBC) {
      f32 tHit=currBC/(currBC-prevBC);
      outXYZW.push_back(currXYZW+tHit*(prevXYZW-currXYZW));
      std::valarray<f32>* hitUV=new std::valarray<f32>(prevUV);
      *hitUV-=currUV;
      *hitUV*=tHit;
      *hitUV+=currUV;
      outUV.push_back(hitUV);        
    }
    if (0 < currBC) {
      outXYZW.push_back(currXYZW);
      outUV.push_back(new std::valarray<f32>(currUV));
    }
  }
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
    if (0 < currBC) {
      outXYZW.push_back(inXYZW[i]);
      outUV.push_back(inUV[i]);
    }
  }
}
}

std::vector<Vec4> HomogeneousClipper::clipWithInfinitesimalW(Vec4 const& v0,
                                                             Vec4 const& v1,
                                                             Vec4 const& v2) {
    std::vector<Vec4> ret;
    const f32   w = 0.00001f;
    const Vec4* verts[3] = {&v0,&v1,&v2};
    const bool  isIn[3]  = {v0.w>w,v1.w>w,v2.w>w};
    for(int i=0;i<3;++i) {
      int prev=(i+2)%3;
      const Vec4& currVert=*verts[i];
      const Vec4& prevVert=*verts[prev];
      if(isIn[prev] != isIn[i]) {
        const f32 t=(currVert.w-w)/(currVert.w-prevVert.w);
        const Vec4 hit=currVert+t*(prevVert-currVert);
        ret.push_back(hit);
      }
      if(isIn[i])
        ret.push_back(currVert);
    }
    return ret;
}

std::vector<Vec4> HomogeneousClipper::clipWithcanonicalViewVolume(
  Vec4 const& v0,
  Vec4 const& v1,
  Vec4 const& v2) {
  std::vector<Vec4> input;
  input.push_back(v0);
  input.push_back(v1);
  input.push_back(v2);
  std::vector<Vec4> output;

  for(int axis=0;axis<3;++axis) {
    for(int sign=-1;sign<=1;sign+=2) {
      const int vertsNum=input.size();
      for(int i=0;i<vertsNum;++i) {
        const Vec4 prev=input[(i+vertsNum-1)%vertsNum];
        const Vec4 curr=input[i];
        const f32 prevBC=compute_boundary_condition(prev,axis,sign);
        const f32 currBC=compute_boundary_condition(curr,axis,sign);
        if (0 > prevBC*currBC) {
          f32 tHit=currBC/(currBC-prevBC);
          output.push_back(curr+tHit*(prev-curr));
        }
        if (0 < currBC)
          output.push_back(curr);
      }
      output.swap(input);
      output.clear();
    }
  }

  return input;
}


int HomogeneousClipper::clipWithInfinitesimalW(
  int idx0,
  int idx1,
  int idx2,
  const std::vector<Vec4>&                inXYZW,
  const std::vector<std::valarray<f32>*>& inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>*>&       outUV) {

  const f32   w = 0.00001f;
  const Vec4* verts[3] = {
    &inXYZW[idx0],
    &inXYZW[idx1],
    &inXYZW[idx2]
  };
  const std::valarray<f32>* attributes[3] = {
    inUV[idx0],
    inUV[idx1],
    inUV[idx2]
  };
  int newVertsNum=0;
  const bool  isIn[3]  = {verts[0]->w>w,verts[1]->w>w,verts[2]->w>w};
  for(int i=0;i<3;++i) {
    int prev=(i+2)%3;
    const Vec4& currVert=*verts[i];
    const Vec4& prevVert=*verts[prev];
    const std::valarray<f32>& currAttribute=*attributes[i];
    const std::valarray<f32>& prevAttribute=*attributes[prev];
    if(isIn[prev] != isIn[i]) {
      const f32 t=(currVert.w-w)/(currVert.w-prevVert.w);
      const Vec4 hit=currVert+t*(prevVert-currVert);
      //std::valarray<f32> hitUv=
      outXYZW.push_back(hit);
      std::valarray<f32>* hitAttribute=new std::valarray<f32>(prevAttribute);
      *hitAttribute-=currAttribute;
      *hitAttribute*=t;
      *hitAttribute+=currAttribute;
      outUV.push_back(hitAttribute);
      ++newVertsNum;
    }
    if(isIn[i]) {
      outXYZW.push_back(currVert);
      outUV.push_back(new std::valarray<f32>(currAttribute));
      ++newVertsNum;
    }
  }

  return newVertsNum;
}

int HomogeneousClipper::clipWithcanonicalViewVolume(
  int idx0,
  int idx1,
  int idx2,
  const std::vector<Vec4>&                inXYZW,
  const std::vector<std::valarray<f32>*>& inUV,
  std::vector<Vec4>&                      outXYZW,
  std::vector<std::valarray<f32>*>&       outUV) {

  std::vector<Vec4> interInXYZW;
  interInXYZW.push_back(inXYZW[idx0]);
  interInXYZW.push_back(inXYZW[idx1]);
  interInXYZW.push_back(inXYZW[idx2]);
  std::vector<std::valarray<f32>*> interInUV;
  interInUV.push_back(new std::valarray<f32>(*inUV[idx0]));
  interInUV.push_back(new std::valarray<f32>(*inUV[idx1]));
  interInUV.push_back(new std::valarray<f32>(*inUV[idx2]));

  std::vector<Vec4>                interOutXYZW;
  std::vector<std::valarray<f32>*> interOutUV;

  for(int axis=0;axis<3;++axis) {
    for(int sign=-1;sign<=1;sign+=2) {
      homogeneous_clip_view_unit_plane(axis,
        sign,
        interInXYZW,
        interInUV,
        interOutXYZW,
        interOutUV);
      interInXYZW.clear();
      interInXYZW.swap(interOutXYZW);

      std::for_each(interInUV.begin(), // delete intermediate valarrays
        interInUV.end(),
        [](std::valarray<f32>* p) {
          delete p;
      });
      interInUV.clear();
      interInUV.swap(interOutUV);
    }
  }

  const int newVertNum=interInXYZW.size();
  std::copy(interInXYZW.begin(),interInXYZW.end(),back_inserter(outXYZW));
  std::copy(interInUV.begin(),interInUV.end(),back_inserter(outUV));
  // remakr(jieyang@gmail.com): no need to delete valarray in interInUV, 
  // since we have "moved" all of them to output
  return newVertNum;
}

int HomogeneousClipper::clipWithInfinitesimalW(
  u32                    primitiveIndex,
  const PrimitiveStream& inStream,
  PrimitiveStream&       outStream) {
  assert(PrimitiveType::TriangleList==inStream.primitiveType());

  const f32 w=0.00001f;
  const u32 idxStart=primitiveIndex*3;
  const Vec4* xyzw[3]={
    &inStream.xyzwAt(idxStart),
    &inStream.xyzwAt(idxStart+1),
    &inStream.xyzwAt(idxStart+2),
  };
  const std::valarray<f32>* uv[3]={
    &inStream.uvAt(idxStart),
    &inStream.uvAt(idxStart+1),
    &inStream.uvAt(idxStart+2),
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

  u32 startIndex=primitiveIndex*3;
  PrimitiveStream::XYZWVec_t inXYZW;
  inXYZW.push_back(inStream.xyzwAt(startIndex));
  inXYZW.push_back(inStream.xyzwAt(startIndex+1));
  inXYZW.push_back(inStream.xyzwAt(startIndex+2));
  PrimitiveStream::UVVec_t   inUV;
  inUV.push_back(inStream.uvAt(startIndex));
  inUV.push_back(inStream.uvAt(startIndex+1));
  inUV.push_back(inStream.uvAt(startIndex+2));
  
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