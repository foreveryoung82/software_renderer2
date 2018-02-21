#include <crtdbg.h>
#include <cassert>

#include "windy/core/applicationwin32.h"
#include "cod/demo.h"

void main() {
  int flag=_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
  flag |= _CRTDBG_LEAK_CHECK_DF;
  _CrtSetDbgFlag(flag);
  {
    windy::ApplicationWin32 app;
    app.run(cod::Demo());
  }
  return;
}