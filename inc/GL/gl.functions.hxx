#pragma once

namespace game
{
  enum class FunctionID : size_t {
#define GLFUNCTION(name, UPPER) \
  UPPER,
#include "GL/gl.functions.inc"
#undef GLFUNCTION
#define WGLFUNCTION(name, UPPER) \
  UPPER,
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION
    count
  };

  struct GL
  {
#define GLFUNCTION(name, UPPER) \
  PFNGL ## UPPER ## PROC name;
#include "GL/gl.functions.inc"
#undef GLFUNCTION

#define WGLFUNCTION(name, UPPER) \
  PFNWGL ## UPPER ## PROC name;
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION

    void init(void);
  };
}