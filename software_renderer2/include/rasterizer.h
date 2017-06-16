//@date:2016.8.30
//@author:yangjie82@gmail.com
//@brief:simple rasterizer
#include <vector>
#include "base.h"
class Framebuffer;
class PrimitiveStream;
class Triangle;

class Rasterizer {
 public:
  Rasterizer(Framebuffer& framebuffer);
  ~Rasterizer();
  int width() const;
  int height() const;
  void setPixelAt(int x, int y, int color);
  //int getPixelAt(int x, int y) const;
  void draw(const Triangle& tri);
  void draw(const PrimitiveStream& stream);
  //void present() const;
 
 private:
  void drawTriangle(const Triangle& tri);
  void drawTriangle(u32 primitiveIndex,const PrimitiveStream& stream);
  int width_;
  int height_;
  //std::vector<int> buffer_;
  Framebuffer* framebuffer_;

  Rasterizer(const Rasterizer& rhs);
  Rasterizer& operator=(const Rasterizer& rhs);
};