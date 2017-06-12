#include "clip.h"
#include <cassert>
#include <algorithm>
#include <iterator>
#include "rect.h"
#include "triangle.h"
#include "triangle3d.h"

std::vector<Vec2> viewport_clip_top(const std::vector<Vec2>& input) {
  std::vector<Vec2> output;
  const int input_num=static_cast<int>(input.size());
  for (int edgeIdx=0;edgeIdx<input_num;++edgeIdx) {
    const Vec2& s=input[edgeIdx];
    const Vec2& t=input[(edgeIdx+1)%input_num];
    const bool s_in=(1>=s.y);
    const bool t_in=(1>=t.y);

    if (!s_in && !t_in)
      continue;
    if (s_in && t_in) {
      output.push_back(t);
      continue;
    }
    f32 cx=s.x+(1-s.y)/(t.y-s.y)*(t.x-s.x);
    output.push_back(Vec2::make(cx,1));
    if (!s_in && t_in)
      output.push_back(t);
  }
  return output;
}

std::vector<Vec2> viewport_clip_bottom(const std::vector<Vec2>& input) {
  std::vector<Vec2> output;
  const int input_num=static_cast<int>(input.size());
  for (int edgeIdx=0;edgeIdx<input_num;++edgeIdx) {
    const Vec2& s=input[edgeIdx];
    const Vec2& t=input[(edgeIdx+1)%input_num];
    const bool s_in=(-1<=s.y);
    const bool t_in=(-1<=t.y);

    if (!s_in && !t_in)
      continue;
    if (s_in && t_in) {
      output.push_back(t);
      continue;
    }
    f32 cx=s.x+(-1-s.y)/(t.y-s.y)*(t.x-s.x);
    output.push_back(Vec2::make(cx,-1));
    if (!s_in && t_in)
      output.push_back(t);
  }
  return output;
}

std::vector<Vec2> viewport_clip_right(const std::vector<Vec2>& input) {
  std::vector<Vec2> output;
  const int input_num=static_cast<int>(input.size());
  for (int edgeIdx=0;edgeIdx<input_num;++edgeIdx) {
    const Vec2& s=input[edgeIdx];
    const Vec2& t=input[(edgeIdx+1)%input_num];
    const bool s_in=(1>=s.x);
    const bool t_in=(1>=t.x);

    if (!s_in && !t_in)
      continue;
    if (s_in && t_in) {
      output.push_back(t);
      continue;
    }
    f32 cy=s.y+(1-s.x)/(t.x-s.x)*(t.y-s.y);
    output.push_back(Vec2::make(1,cy));
    if (!s_in && t_in)
      output.push_back(t);
  }
  return output;
}

std::vector<Vec2> viewport_clip_left(const std::vector<Vec2>& input) {
  std::vector<Vec2> output;
  const int input_num=static_cast<int>(input.size());
  for (int edgeIdx=0;edgeIdx<input_num;++edgeIdx) {
    const Vec2& s=input[edgeIdx];
    const Vec2& t=input[(edgeIdx+1)%input_num];
    const bool s_in=(-1<=s.x);
    const bool t_in=(-1<=t.x);

    if (!s_in && !t_in)
      continue;
    if (s_in && t_in) {
      output.push_back(t);
      continue;
    }
    f32 cy=s.y+(-1-s.x)/(t.x-s.x)*(t.y-s.y);
    output.push_back(Vec2::make(-1,cy));
    if (!s_in && t_in)
      output.push_back(t);
  }
  return output;
}

std::vector<Vec2> viewport_clip( const Triangle& triangle ) {
  // Sutherland¨CHodgman clip algorithm
  std::vector<Vec2> input(triangle.m, triangle.m+3);
  std::vector<Vec2> output=viewport_clip_top(input);
  output=viewport_clip_bottom(output);
  output=viewport_clip_right(output);
  output=viewport_clip_left(output);

  // remove repeated vertices
  output.erase(std::unique(output.begin(),output.end()),
               output.end());
  return output;
}

std::vector<Vec4> homogeneous_clip(Vec4 const& a,Vec4 const& c) {
  std::vector<Vec4> ret;

  f32 bcA[6];
  f32 bcC[6];
  for(int i=0;i<3;++i) {
    bcA[i*2]  = a[3]+a[i];
    bcA[i*2+1]= a[3]-a[i];
    bcC[i*2]  = c[3]+c[i];
    bcC[i*2+1]= c[3]-c[i];
  }
  u8 outcomeA=0;
  u8 outcomeC=0;
  for(int i=0;i<6;++i) {
    const u8 flag=0x1<<i;
    if(0>=bcA[i])
      outcomeA|=flag;
    if(0>=bcC[i])
      outcomeC|=flag;
  }

  if((outcomeA & outcomeC) != 0) // at least one plane keeps both points out
    return ret;
  if((outcomeA | outcomeC) == 0) { // both points are in box
    ret.push_back(a);
    ret.push_back(c);
    return ret;
  }

  f32 tIn  = 0.f;
  f32 tOut = 1.f;
  for(int i=0;i<6;++i) {
    f32 t=bcA[i]/(bcA[i]-bcC[i]);
    if(0 > bcA[i])
      tIn=std::max(t,tIn);
    else if (0 > bcC[i])
      tOut=std::min(t,tOut);
    if(tIn>tOut)
      return ret;
  }

  Vec4 newA=Vec4::make(a.x+(c.x-a.x)*tIn,
                       a.y+(c.y-a.y)*tIn,
                       a.z+(c.z-a.z)*tIn,
                       a.w+(c.w-a.w)*tIn);
  Vec4 newC=Vec4::make(a.x+(c.x-a.x)*tOut,
                       a.y+(c.y-a.y)*tOut,
                       a.z+(c.z-a.z)*tOut,
                       a.w+(c.w-a.w)*tOut);
  ret.push_back(newA);
  ret.push_back(newC);
  return ret;
}

//std::vector<Triangle3D> homogenous_clip(Vec4 const& v0,
//                                        Vec4 const& v1,
//                                        Vec4 const& v2) {
//  const Vec4* tri[3]={&v0,&v1,&v2}; 
//  std::vector<Vec4> vertexes;
//  for(int i=0;i<3;++i) {
//    Vec4 const& a=*tri[i];
//    Vec4 const& c=*tri[(i+1)%3];
//    std::vector<Vec4> newVerts=homogenous_clip(a,c);
//    for(auto vert:newVerts) {
//      Vec4 temp=vert*(1.f/vert.w);
//      vertexes.push_back(temp);
//    }
//    //std::copy(newVerts.begin(),newVerts.end(),back_inserter(vertexes));  
//  }
//
//  std::vector<Triangle3D> triangles;
//  const int num=vertexes.size();
//  for(int i=0;i<num-2;++i) {
//    triangles.push_back(Triangle3D::make(Vec3::make(vertexes[0]),
//                                         Vec3::make(vertexes[i+1]),
//                                         Vec3::make(vertexes[(i+2)%num])));
//  }
//  return triangles;
//}

std::vector<Vec4> homogeneous_clip(Vec4 const& v0,
                                  Vec4 const& v1,
                                  Vec4 const& v2) {
  const Vec4* tri[3]={&v0,&v1,&v2}; 
  std::vector<Vec4> ret;
  for(int i=0;i<3;++i) {
    Vec4 const& a=*tri[i];
    Vec4 const& c=*tri[(i+1)%3];
    std::vector<Vec4> verts=homogeneous_clip(a,c);
    std::copy(verts.begin(),verts.end(),back_inserter(ret));
  }
  return ret;
}

std::vector<Vec4> homogeneous_clip_infinitesimal_w(Vec4 const& v0,
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

f32 compute_boundary_condition(Vec4 const& v,int axis,int sign) {
  return (v[3]-sign*v[axis]);
}

std::vector<Vec4> homogeneous_clip_view_frustum(Vec4 const& v0,
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