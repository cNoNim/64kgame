#include "stdafx.hxx"
#include "game.hxx"

EXTERN_C INT _fltused = 0;

void
entrypoint(void)
{
  using namespace game;
  ExitProcess(application::instance().run());
}
