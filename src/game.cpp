#include "stdafx.hxx"
#include "game.hxx"

static LRESULT CALLBACK WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam);

namespace game
{
  app::app(HINSTANCE instance, bool fullscreen) : 
    instance(instance),
    window((
      [](HINSTANCE instance, bool fullscreen) { 
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

        auto window = CreateWindowEx( styleEx, wc.lpszClassName, wc.lpszClassName, style,
                                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                    nullptr, nullptr, instance, nullptr);
        if (!window) Error(TEXT("Can't create window"));
        return window;
      })(instance, fullscreen)),
    device((
      [] (HWND window) {
        auto device = GetDC(window); 
        if (!device) Error(TEXT("Can't get device context"));
        return device;
      })(window)),
    context(device)
  {
    SetForegroundWindow(window);
    SetFocus(window);
  }

  app::~app(void) {}

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
