#pragma once

extern struct WGL
{
#define WGLFUNCTION(name, UPPER) \
  PFNWGL ## UPPER ## PROC name;
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION

  void init(void);
} wgl;
