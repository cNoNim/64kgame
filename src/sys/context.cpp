#include "stdafx.hxx"
#include "sys/context.hxx"

#include "GL/gl.functions.hxx"
#include "GL/wgl.functions.hxx"

void createContext(HWND window)
{
  static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32, 0, 0, 0, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0,
    24,
    8,
    0,
    PFD_MAIN_PLANE,
    0, 0, 0, 0
  };

  auto device = GetDC(window);
  auto format = ChoosePixelFormat(device, &pfd);
  SetPixelFormat(device, format, &pfd);

  auto tempContext = wglCreateContext(device);
  wglMakeCurrent(device, tempContext);
  wgl.init();

  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(tempContext);

  int attribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 0,
    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0, 0
  };

  auto rc = wgl.CreateContextAttribsARB(device, nullptr, attribs);
  wglMakeCurrent(device, rc);
  gl.init();
}

void destroyContext(HWND window)
{
  auto device = wglGetCurrentDC();
  auto rc = wglGetCurrentContext();
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(rc);
  ReleaseDC(window, device);
}
