#pragma once

#include "GL/gl.functions.hxx"

namespace game
{
  class application
  {
    GL gl;
    void * window;
  public:
    static application & instance(void);
    int run(void);
  private:
    application(void);
    application(application const &);
    ~application(void) {}
  };
}
