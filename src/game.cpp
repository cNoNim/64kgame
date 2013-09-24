#include "stdafx.h"
#include "game.h"

static LRESULT CALLBACK WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam);

extern const PIXELFORMATDESCRIPTOR pfd;

namespace game
{
  app::app(HINSTANCE instance) : 
    instance(instance),
    window(nullptr),
    device(nullptr),
    context(nullptr),
    fullscreen(YesNo(TEXT("Run in fullscreen?")))
  {
    DWORD styleEx = WS_EX_APPWINDOW, 
      style = WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    WNDCLASS wc = { 0 };

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = TEXT("64k_game");

    if (!RegisterClass(&wc)) Error(TEXT("Can't register class"));

    if (fullscreen) {
      style |= WS_POPUP;
		  ShowCursor( 0 );
    } else {
      style |= WS_CAPTION | WS_SYSMENU;
    }

    window = CreateWindowEx( styleEx, wc.lpszClassName, wc.lpszClassName, style,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                nullptr, nullptr, instance, nullptr);
    if (!window) Error(TEXT("Can't create window"));

    device = GetDC(window); 
    if (!device) Error(TEXT("Can't get device context"));

    auto format = ChoosePixelFormat(device, &pfd);
    if (!format) Error(TEXT("Can't choose pixel format"));
    if (!SetPixelFormat(device, format, &pfd)) Error(TEXT("Can't set pixel format"));
    
    context = wglCreateContext(device);
    if (!context) Error(TEXT("Can't create rendering context"));
    if (!wglMakeCurrent(device, context)) Error(TEXT("Can't set rendering context"));

    SetForegroundWindow(window);
    SetFocus(window);
  }

  int 
  app::run(void)
  {
    MSG msg = { 0 };
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    while(msg.message != WM_QUIT)
    {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        DispatchMessage(&msg);
      else {
        tick();
        SwapBuffers(device);
      }
    }
    return EXIT_SUCCESS;
  }

  void
  app::tick(void)
  {
    glClear( GL_COLOR_BUFFER_BIT );
  }
}

static LRESULT CALLBACK
WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_CLOSE || 
    (message == WM_KEYDOWN && wParam==VK_ESCAPE) )
	{
    PostQuitMessage(0);
    return 0 ;
	}

  return DefWindowProc(window, message, wParam, lParam);
}

const PIXELFORMATDESCRIPTOR pfd = {
  sizeof(PIXELFORMATDESCRIPTOR),
  1,
  PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
  PFD_TYPE_RGBA,
  32,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  32,             // zbuffer
  0,              // stencil!
  0,
  PFD_MAIN_PLANE,
  0, 0, 0, 0
};