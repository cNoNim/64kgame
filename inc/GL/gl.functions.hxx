#pragma once

namespace game
{
  enum class GLFunction : size_t {
#define GLFUNCTION(name, UPPER) \
  UPPER,
#include "GL/gl.functions.inc"
#undef GLFUNCTION
    count
  };

  struct GL
  {
#define GLFUNCTION(name, UPPER) \
  PFNGL ## UPPER ## PROC name;
#include "GL/gl.functions.inc"
#undef GLFUNCTION

    void init(void);
  };
}