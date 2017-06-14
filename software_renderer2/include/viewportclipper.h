//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:clip triangle by rectangle
#include <vector>
#include "vec2.h"
class Triangle;

class ViewportClipper {
 public:
  static std::vector<Vec2> clip(const Triangle& triangle);
};
