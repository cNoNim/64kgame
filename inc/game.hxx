#pragma once

#include "GL/gl.context.hxx"

namespace game
{
  class app
  {
  public:
    app(HINSTANCE instance, bool fullscreen = false);
    ~app(void);
    int run(void);
    void tick(void);
  private:
    HINSTANCE instance;
    HWND window;
    HDC device;
    gl::GLContext context;
  };
}
