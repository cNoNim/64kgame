#pragma once

namespace gl
{
  enum class FunctionID : size_t {
#define GLFUNCTION(name, UPPER) \
  UPPER,
#include <GL/gl.functions.inc>
#undef GLFUNCTION
    count
  };

  struct GLContext
  {
    HGLRC rc;

#define GLFUNCTION(name, UPPER) \
  PFNGL ## UPPER ## PROC name;
#include "GL/gl.functions.inc"
#undef GLFUNCTION

    GLContext(HDC device);
    ~GLContext();
  };
}