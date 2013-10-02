#include "stdafx.hxx"
#include "GL/gl.functions.hxx"

namespace game
{
  void 
  GL::init(void)
  {
    static char const FunctionNames[] = {
#define GLFUNCTION(name, UPPER) \
  "gl"STRING(name)"\0"
#include "GL/gl.functions.inc"
#undef GLFUNCTION
#define WGLFUNCTION(name, UPPER) \
  "wgl"STRING(name)"\0"
#include "GL/wgl.functions.inc"
#undef WGLFUNCTION
      ""
    };
  
    auto procs = reinterpret_cast<PROC *>(this);
    char const * str = FunctionNames;      
    size_t ID = 0;
    for (; ID < static_cast<size_t>(FunctionID::count); ++ID)
    {
      PROC &current = procs[ID];
      current = wglGetProcAddress( str );
      if( !current ) break;        
      str += strlen( str ) + 1;     
    }
      
    if (FunctionID::count != static_cast<FunctionID>(ID)) Raise(error::GLFunctionInitialization);
  }

}
