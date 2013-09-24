#include <stdafx.h>

#define STRINGIFY(str) #str

namespace gl
{

#define GLFUNCTION(name, UPPER) \
  UPPER,

  enum class FunctionID {
#include <GL/glfunctions.h>
    count
  };
#undef GLFUNCTION

#define GLFUNCTION(name, UPPER) \
  "gl"STRINGIFY(name)"\x0"

  static char FunctionNames[] = {
#include <GL/glfunctions.h>
    ""
  };
#undef GLFUNCTION

  PROC Functions[FunctionID::count];

  void
  init(void) 
  {
    char *str = FunctionNames;
    for (int ID = 0,
             count = static_cast<int>(FunctionID::count); 
     ID < count; ID++)
    {
      Functions[ID] = wglGetProcAddress(str);
      str += strlen(str) + 1;
      if (!Functions[ID]) game::Error(TEXT("Function not supported"));
    }
  }
}