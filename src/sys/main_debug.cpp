#include "stdafx.hxx"
#include "game.hxx"

int WINAPI
_tWinMain(HINSTANCE /*instance*/, 
          HINSTANCE /*prevInstance*/, 
          LPTSTR /*cmdLine*/, 
          int /*show*/)
{
  using namespace game;
  return application::instance().run();
}
