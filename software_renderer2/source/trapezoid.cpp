#include "trapezoid.h"
#include <algorithm>
#include "triangle.h"

int divide_into_trapezoids(const Triangle& triangle, Trapezoid* trapezoids) {
  // remove case when triangle degenerate into line
  const bool is_vline=((triangle.p0.x==triangle.p1.x) &&
                       (triangle.p0.x==triangle.p2.x));
  if (is_vline) return 0;
  const bool is_hline=((triangle.p0.y==triangle.p1.y) &&
                       (triangle.p0.y==triangle.p2.y));
  if (is_hline) return 0;

  Vec2 v[3];
  std::copy(triangle.m, triangle.m+3, v);
  std::sort(v, v+3,
            [](Vec2 const& a, Vec2 const& b){return a.y>b.y;}
  );

  const bool is_hedge_at_top=(v[0].y==v[1].y);
  if (is_hedge_at_top) {
    if (v[0].x>v[1].x)
      std::swap(v[0], v[1]);
    Trapezoid& t=trapezoids[0];
    t.l=Line2::make(v[0], v[2]);
    t.r=Line2::make(v[1], v[2]);
    t.t=v[0].y;
    t.b=v[2].y;
    return 1;
  }
  const bool is_hedge_at_bottom=(v[2].y==v[1].y);
  if (is_hedge_at_bottom) {
    if (v[1].x>v[2].x)
      std::swap(v[1], v[2]);
    Trapezoid& t=trapezoids[0];
    t.l=Line2::make(v[0], v[1]);
    t.r=Line2::make(v[0], v[2]);
    t.t=v[0].y;
    t.b=v[2].y;
    return 1;
  }

  float x=(v[1].y-v[0].y)/(v[2].y-v[0].y)*(v[2].x-v[0].x)+v[0].x;
  if (x<v[1].x) { // scan line touch [v0,v2] first
    trapezoids[0].l=Line2::make(v[0],v[2]);
    trapezoids[0].r=Line2::make(v[0],v[1]);
    trapezoids[0].t=v[0].y;
    trapezoids[0].b=v[1].y;
    trapezoids[1].l=Line2::make(v[0],v[2]);
    trapezoids[1].r=Line2::make(v[1],v[2]);
    trapezoids[1].t=v[1].y;
    trapezoids[1].b=v[2].y;
  } else {
    trapezoids[0].l=Line2::make(v[0],v[1]);
    trapezoids[0].r=Line2::make(v[0],v[2]);
    trapezoids[0].t=v[0].y;
    trapezoids[0].b=v[1].y;
    trapezoids[1].l=Line2::make(v[0],v[1]);
    trapezoids[1].r=Line2::make(v[1],v[2]);
    trapezoids[1].t=v[1].y;
    trapezoids[1].b=v[2].y;
  }
  return 2;
}