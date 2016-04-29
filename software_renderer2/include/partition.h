//@date:2016.4.24
//@author:jieyang@moonton.com
//@brief:��ֱ�߻���ƽ�棬�жϼ�������ֱ�ߵ���࣬�Ҳ������ֱ����
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
