#include "stdafx.h"
#include "game.h"

extern "C" int _fltused = 0;

void 
entrypoint(void)
{
  using namespace game;
  app app(GetModuleHandle(nullptr));
  auto status = app.run();
  ExitProcess(status);
}
