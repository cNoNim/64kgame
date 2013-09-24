#include "stdafx.h"
#include "game.h"

void 
entrypoint(void)
{
  using namespace game;
  app app(GetModuleHandle(nullptr));
  auto status = app.run();
  ExitProcess(status);
}