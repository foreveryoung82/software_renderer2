#include "viewportclipper.h"
#include <algorithm>
#include "triangle.h"

namespace {
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
}

std::vector<Vec2> ViewportClipper::clip(const Triangle& triangle) {
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

