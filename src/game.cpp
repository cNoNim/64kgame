#include "stdafx.hxx"
#include "game.hxx"

void init()
{
  MessageBoxA(nullptr, resources::foo().data(), "", 0);
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void update()
{
}
