#include "trapezoid.h"
#include <algorithm>
#include "primitivestream.h"
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

  f32 x=(v[1].y-v[0].y)/(v[2].y-v[0].y)*(v[2].x-v[0].x)+v[0].x;
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
    trapezoids[1].l=Line2::make(v[1],v[2]);
    trapezoids[1].r=Line2::make(v[0],v[2]);
    trapezoids[1].t=v[1].y;
    trapezoids[1].b=v[2].y;
  }
  return 2;
}

int divide_into_trapezoids(u32                    primitiveIndex,
                           const PrimitiveStream& stream,
                           IndexedTrapezoid*      trapezoids) {
  u32 tri[3]={0,1,2};
  const u32 indexBaseIndex=primitiveIndex*3;
  const u32 indexes[3] = {
    stream.indexAt(indexBaseIndex),
    stream.indexAt(indexBaseIndex+1),
    stream.indexAt(indexBaseIndex+2),
  };
  const Vec4* xyzw[3]={
    &stream.xyzwAt(indexes[0]),
    &stream.xyzwAt(indexes[1]),
    &stream.xyzwAt(indexes[2]),
  };

  auto v=[&xyzw,&tri](u8 idx) {return xyzw[tri[idx]];};
  // remove case when triangle degenerate into line
  const bool is_vline=((v(0)->x==v(1)->x) && (v(0)->x==v(2)->x));
  if (is_vline) return 0;
  const bool is_hline=((v(0)->y==v(1)->y) && (v(0)->y==v(2)->y));
  if (is_hline) return 0;

  std::sort(tri,tri+3,[&xyzw](u32 a,u32 b){
    return (xyzw[a]->y > xyzw[b]->y);
  });

  const bool is_hedge_at_top=(v(0)->y==v(1)->y);
  if (is_hedge_at_top) {
    if (v(0)->x > v(1)->x)
      std::swap(tri[0], tri[1]);
    IndexedTrapezoid& t=trapezoids[0];
    t.l[0]=indexes[tri[0]];
    t.l[1]=indexes[tri[2]];
    t.r[0]=indexes[tri[1]];
    t.r[1]=indexes[tri[2]];
    t.t=v(0)->y;
    t.b=v(2)->y;
    return 1;
  }
  const bool is_hedge_at_bottom=(v(2)->y==v(1)->y);
  if (is_hedge_at_bottom) {
    if (v(1)->x > v(2)->x)
      std::swap(tri[1], tri[2]);
    IndexedTrapezoid& t=trapezoids[0];
    t.l[0]=indexes[tri[0]];
    t.l[1]=indexes[tri[1]];
    t.r[0]=indexes[tri[0]];
    t.r[1]=indexes[tri[2]];
    t.t=v(0)->y;
    t.b=v(2)->y;
    return 1;
  }

  const f32 x=(v(1)->y-v(0)->y) / (v(2)->y-v(0)->y)*(v(2)->x-v(0)->x)+v(0)->x;
  if (x<v(1)->x) { // scan line touch [v0,v2] first
    trapezoids[0].l[0]=indexes[tri[0]];
    trapezoids[0].l[1]=indexes[tri[2]];
    trapezoids[0].r[0]=indexes[tri[0]];
    trapezoids[0].r[1]=indexes[tri[1]];
    trapezoids[0].t=v(0)->y;
    trapezoids[0].b=v(1)->y;
    trapezoids[1].l[0]=indexes[tri[0]];
    trapezoids[1].l[1]=indexes[tri[2]];
    trapezoids[1].r[0]=indexes[tri[1]];
    trapezoids[1].r[1]=indexes[tri[2]];
    trapezoids[1].t=v(1)->y;
    trapezoids[1].b=v(2)->y;
  } else {
    trapezoids[0].l[0]=indexes[tri[0]];
    trapezoids[0].l[1]=indexes[tri[1]];
    trapezoids[0].r[0]=indexes[tri[0]];
    trapezoids[0].r[1]=indexes[tri[2]];
    trapezoids[0].t=v(0)->y;
    trapezoids[0].b=v(1)->y;
    trapezoids[1].l[0]=indexes[tri[1]];
    trapezoids[1].l[1]=indexes[tri[2]];
    trapezoids[1].r[0]=indexes[tri[0]];
    trapezoids[1].r[1]=indexes[tri[2]];
    trapezoids[1].t=v(1)->y;
    trapezoids[1].b=v(2)->y;
  }
  return 2;
}