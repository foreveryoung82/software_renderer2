#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <cassert>

#include "demodepthbuffer.h"

void main() {
  {
    DemoDepthBuffer demo;
    demo.run();
  }
  assert(!_CrtDumpMemoryLeaks());
  return;
}