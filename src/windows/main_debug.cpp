#include "stdafx.h"
#include "game.h"

int WINAPI
_tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR cmdLine, int show)
{
  using namespace game;
  app app(instance);
  auto status = app.run();
  return status;
}
