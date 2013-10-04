#include "stdafx.hxx"
#include "sys/application.hxx"


int WINAPI WinMain(HINSTANCE /*instance*/,
                   HINSTANCE /*prevInstance*/,
                   LPSTR /*cmdLine*/,
                   int /*show*/)
{
  return application::instance().run();
}