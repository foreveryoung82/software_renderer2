//@date:2016.4.24
//@author:jieyang@moonton.com
//@brief:以直线划分平面，判断几何体在直线的左侧，右侧或是在直线上
#pragma once
#include <cstdint>
class Line2;
class Vec2;

enum PartitionResult: std::uint8_t {
  kOnLine,
  kLeft,
  kRight,
};

PartitionResult partition(Line2 const& line, Vec2 const& point);
PartitionResult partition(Line2 const& line, Vec2 const& point, float epsilon);
