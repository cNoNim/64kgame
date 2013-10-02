#include "stdafx.hxx"
#include "GL/wgl.functions.hxx"

namespace game
{
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
  
    auto procs = reinterpret_cast<PROC *>(this);
    char const * str = FunctionNames;      
    size_t ID = 0;
    for (; ID < static_cast<size_t>(WGLFunction::count); ++ID)
    {
      PROC &current = procs[ID];
      current = wglGetProcAddress( str );
      if( !current ) break;        
      str += strlen( str ) + 1;     
    }
      
    if (WGLFunction::count != static_cast<WGLFunction>(ID)) Raise(error::GLFunctionInitialization);
  }

}
