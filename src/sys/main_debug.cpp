#include "stdafx.hxx"
#include "sys/application.hxx"

int WINAPI
_tWinMain(HINSTANCE /*instance*/, 
          HINSTANCE /*prevInstance*/, 
          LPTSTR /*cmdLine*/, 
          int /*show*/)
{
  return application::instance().run();
}
