#pragma once

namespace game
{
  enum class WGLFunction : size_t {
#define WGLFUNCTION(name, UPPER) \
  UPPER,
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION
    count
  };

  struct WGL
  {
#define WGLFUNCTION(name, UPPER) \
  PFNWGL ## UPPER ## PROC name;
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION

    void init(void);
  };
}