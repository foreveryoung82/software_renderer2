//@date:2016.8.30
//@author:yangjie82@gmail.com
//@brief:simple rasterizer
#include <vector>

class Triangle;
class Framebuffer;
class Rasterizer {
 public:
  Rasterizer(Framebuffer& framebuffer);
  ~Rasterizer();
  int width() const;
  int height() const;
  void setPixelAt(int x, int y, int color);
  //int getPixelAt(int x, int y) const;
  void draw(const Triangle& tri);
  //void present() const;
 
 private:
   void drawTriangle(const Triangle& tri);
  int width_;
  int height_;
  //std::vector<int> buffer_;
  Framebuffer* framebuffer_;

  Rasterizer(const Rasterizer& rhs);
  Rasterizer& operator=(const Rasterizer& rhs);
};