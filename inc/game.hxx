#pragma once

#include "GL/gl.context.hxx"

namespace game
{
  class app
  {
  public:
    app(void);
    ~app(void);
    int run(void);
    void tick(void);
  private:
    HWND window;
    HDC device;
    gl::GLContext context;
  };
}
