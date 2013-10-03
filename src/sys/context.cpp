#include "stdafx.hxx"
#include "sys/context.hxx"

#include "GL/gl.functions.hxx"

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

  auto context = wglCreateContext(device);
  wglMakeCurrent(device, context);
  gl.init();
}

void destroyContext(HWND window)
{
  auto device = wglGetCurrentDC();
  auto context = wglGetCurrentContext();
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(context);
  ReleaseDC(window, device);
}
