#include "stdafx.hxx"
#include "GL/gl.context.hxx"

static gl::FunctionID init(gl::GLContext & _this);

namespace gl
{
  GLContext::GLContext(HDC device)
  {
    static const PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      32,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      32,
      0,
      0,
      PFD_MAIN_PLANE,
      0, 0, 0, 0
    };


    auto format = ChoosePixelFormat(device, &pfd);
    if (!format) Error(TEXT("Can't choose pixel format"));
    if (!SetPixelFormat(device, format, &pfd)) Error(TEXT("Can't set pixel format"));
    
    rc = wglCreateContext(device);
    if (!rc) Error(TEXT("Can't create rendering context"));
    if (!wglMakeCurrent(device, rc)) Error(TEXT("Can't set rendering context"));
    if (gl::FunctionID::count != init(*this)) Error(TEXT("Can't initialize GL functions"));
  }

  GLContext::~GLContext(void) {}
}

static gl::FunctionID init(gl::GLContext & _this)
{
  static char const FunctionNames[] = {
#define GLFUNCTION(name, UPPER) \
"gl"STRING(name)"\x0"
#include <GL/gl.functions.inc>
#undef GLFUNCTION
    ""
  };

  struct context { HGLRC _; PROC by_id[gl::FunctionID::count]; } & procs = reinterpret_cast<context &>(_this);

  char const * str = FunctionNames;
    
  size_t ID = 0;
  for (; ID < static_cast<size_t>(gl::FunctionID::count); ID++)
  {
    PROC &current = procs.by_id[ID];
    current = wglGetProcAddress( str );
    if( !current )
      break;        
    str += 1+strlen( str );     
  }
    
  return static_cast<gl::FunctionID>(ID);
}
