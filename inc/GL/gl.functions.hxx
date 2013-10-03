#pragma once

extern struct GL
{
#define GLFUNCTION(name, UPPER) \
PFNGL ## UPPER ## PROC name;
#include "GL/gl.functions.inc"
#undef GLFUNCTION

  void init(void);
} gl;
