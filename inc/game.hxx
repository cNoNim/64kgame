#pragma once

#include "GL/gl.functions.hxx"
#include "GL/wgl.functions.hxx"

namespace game
{
  class application
  {
  public:
    GL & gl;
    WGL & wgl;
    static application & instance(void);
    int run(void);
  private:
    application(GL & gl, WGL & wgl);
    application(application const &);
    application & operator= (application const &);
    ~application(void) {}

  };

  static_assert(sizeof(game::application) <= 4096, "Extend HeapSize");
}
