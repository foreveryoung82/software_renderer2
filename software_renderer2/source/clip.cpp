#include "clip.h"
#include <cassert>
#include <algorithm>
#include <iterator>
#include "intersect.h"
#include "rect.h"
#include "triangle.h"

namespace {
bool is_rect_in_triangle(Rect const& rect, Triangle const& triangle) {
  for (int i=0;i<4;++i)
    if (!intersect(triangle, rect.corner(i)))
      return false;
   return true;
}

bool needPatchGap(IntersectResult const& p, IntersectResult const& q) {
  return (p.rectBoundIdx[1]!=IntersectResult::kInvalidRectEdgeIdx) &&
          (q.rectBoundIdx[0]!=IntersectResult::kInvalidRectEdgeIdx);
}

std::vector<Vec2> patchGap(IntersectResult const& p,
                           IntersectResult const& q,
                           Rect const& rect) {
  std::vector<Vec2> result;
  int i=p.rectBoundIdx[1];
  int j=q.rectBoundIdx[0];
  Vec2 s=p.line.t;
  while (i!=j) {
    //result.push_back(s);
    i=(i+1)%4;
    Vec2 t=rect.corner(i);
    result.push_back(t);
    s=t;
  }
  //result.push_back(s);
  //result.push_back(p.line[0]);
  return result;
}
}

std::vector<Vec2> clip(std::vector<IntersectResult> const& segments,
                       Triangle const& triangle,
                       //std::vector<Vec2> const& rectPts) {
                       Rect const& rect) {
  //assert(4==rectPts.size());
  auto result=std::vector<Vec2>();
  int segmentNum=segments.size();
  if (!segmentNum) {
    if (is_rect_in_triangle(rect, triangle)) {
      for (int i=0;i<4;++i)
        result.push_back(rect.corner(i));
    }
    return result;
  }
  for (int i=0;i<segmentNum;++i) {
    auto j=(i+1)%segmentNum;
    auto& p=segments[i];
    auto& q=segments[j];
    result.push_back(p.line.s);
    result.push_back(p.line.t);
    if (needPatchGap(p,q)) {
      auto gap=patchGap(p,q,rect);
      std::copy(gap.begin(), gap.end(), std::back_inserter(result));
    }
  }
  return result;
}

std::vector<Vec2> viewport_clip_top(const std::vector<Vec2>& input) {
  std::vector<Vec2> output;
  const int input_num=static_cast<int>(input.size());
  for (int edgeIdx=0;edgeIdx<input_num;++edgeIdx) {
    const Vec2& s=input[edgeIdx];
    const Vec2& t=input[(edgeIdx+1)%input_num];
    
    if ((1<s.y) && (1<t.y))
      continue;
    if ((1>s.y) && (1>t.y)) {
      output.push_back(t);
      continue;
    }
    float cx=s.x+(1-s.y)/(t.y-s.y)*(t.x-s.x);
    output.push_back(Vec2::make(cx,1));
    if ((1<s.y) && (1>t.y))
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

    if ((-1>s.y) && (-1>t.y))
      continue;
    if ((-1<s.y) && (-1<t.y)) {
      output.push_back(t);
      continue;
    } 
    float cx=s.x+(-1-s.y)/(t.y-s.y)*(t.x-s.x);
    output.push_back(Vec2::make(cx,-1));
    if ((-1>s.y) && (-1<t.y))
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

    if ((1<s.x) && (1<t.x))
      continue;
    if ((1>s.x) && (1>t.x)) {
      output.push_back(t);
      continue;
    }
    float cy=s.y+(1-s.x)/(t.x-s.x)*(t.y-s.y);
    output.push_back(Vec2::make(1,cy));
    if ((1<s.x) && (1>t.x))
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

    if ((-1>s.x) && (-1>t.x))
      continue;
    if ((-1<s.x) && (-1<t.x)) {
      output.push_back(t);
      continue;
    }
    float cy=s.y+(-1-s.x)/(t.x-s.x)*(t.y-s.y);
    output.push_back(Vec2::make(-1,cy));
    if ((-1>s.x) && (-1<t.x))
      output.push_back(t);
  }
  return output;
}

std::vector<Vec2> viewport_clip( const Triangle& triangle ) {
  // sutherland dogeman clip algorithm
  std::vector<Vec2> input(triangle.m, triangle.m+3);
  std::vector<Vec2> output=viewport_clip_top(input);
  output=viewport_clip_bottom(output);
  output=viewport_clip_right(output);
  output=viewport_clip_left(output);
  return output;
}
