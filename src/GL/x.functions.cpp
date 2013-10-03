#include "stdafx.hxx"
#include "GL/gl.functions.hxx"
#include "GL/wgl.functions.hxx"

static void initFunctions(char const * functionNames, PROC * funstions, size_t count);

GL gl;
WGL wgl;

void 
GL::init(void)
{
  static char const FunctionNames[] = {
#define GLFUNCTION(name, UPPER) \
  "gl"STRING(name)"\0"
#include "GL/gl.functions.inc"
#undef GLFUNCTION
    ""
  };
  
  initFunctions(FunctionNames, reinterpret_cast<PROC *>(this), sizeof(GL) / sizeof(PROC *));
}

void
WGL::init(void)
{
  static char const FunctionNames[] = {
#define WGLFUNCTION(name, UPPER) \
  "wgl"STRING(name)"\0"
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION
    ""
  };

  initFunctions(FunctionNames, reinterpret_cast<PROC *>(this), sizeof(WGL) / sizeof(PROC *));
}

static void initFunctions(char const * functionNames, PROC * funstions, size_t count)
{
  for (size_t ID = 0; ID < count; ++ID) {
    PROC &current = funstions[ID];
    current = wglGetProcAddress(functionNames);
    if (!current) Raise(error::GLFunctionInitialization);
    functionNames += strlen(functionNames) + 1;
  }
}
