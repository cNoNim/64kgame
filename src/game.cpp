#include "stdafx.hxx"
#include "game.hxx"

static LRESULT CALLBACK WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam);

namespace game
{
  app::app(void) : 
    window((
      []() { 
        DWORD styleEx = WS_EX_APPWINDOW, 
          style = WS_VISIBLE | WS_SIZEBOX | WS_POPUP;

        WNDCLASS wc = { 0 };

        wc.style = CS_OWNDC;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = THIS_INSTANCE;
        wc.lpszClassName = TEXT("64k_game");

        if (!RegisterClass(&wc)) Error(TEXT("Can't register class"));

        auto window = CreateWindowEx( styleEx, wc.lpszClassName, wc.lpszClassName, style,
                                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                    nullptr, nullptr, THIS_INSTANCE, nullptr);
        if (!window) Error(TEXT("Can't create window"));
        return window;
      })()),
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

static LRESULT HitTest(HWND window, WPARAM wParam, LPARAM lParam) 
{
  UNREFERENCED_PARAMETER(wParam);
  POINT mouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
  RECT windowRect;
  GetWindowRect(window, &windowRect);
  RECT frameRect = { 0 };
  AdjustWindowRectEx(&frameRect, WS_VISIBLE | WS_SIZEBOX | WS_POPUP | WS_CAPTION, FALSE, WS_EX_APPWINDOW);
  
  bool onBorder = false;
  short row = 0, col = 0;

  if ((mouse.y >= windowRect.top) 
    && (mouse.y < windowRect.top - frameRect.bottom)) {
    onBorder = mouse.y < (windowRect.top - frameRect.top);
    row = -1;
  } else if ( (mouse.y < windowRect.bottom) 
           && (mouse.y >= windowRect.bottom - frameRect.bottom)) {
    row = 1;
  }

  if ( (mouse.x >= windowRect.left)
    && (mouse.x < windowRect.left - frameRect.left)) {
    col = -1;
  } else if ( (mouse.x < windowRect.right)
           && (mouse.x >= windowRect.right - frameRect.right)) {
    col = 1;
  }


  LRESULT hitTest[3][3] = {
    { HTTOPLEFT,    onBorder ? HTTOP : HTCAPTION, HTTOPRIGHT    },
    { HTLEFT,       HTNOWHERE,                    HTRIGHT       },
    { HTBOTTOMLEFT, HTBOTTOM,                     HTBOTTOMRIGHT }
  };

  return hitTest[row + 1][col + 1];
}

static LRESULT CALLBACK
WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_CREATE) {
    RECT rect;
    GetWindowRect(window, &rect);

    SetWindowPos(window, 
      NULL, 
      rect.left, rect.top,
      RECTWIDTH(rect), RECTHEIGHT(rect),
      SWP_FRAMECHANGED);
  }

  if (message == WM_ACTIVATE) {
    MARGINS margins = { 0 };
    DwmExtendFrameIntoClientArea(window, &margins);
    return 0;
  }

  if ((message == WM_NCCALCSIZE) && (wParam == TRUE)) {
    return 0;
  }

  if (message == WM_NCHITTEST) {
    return HitTest(window, wParam, lParam);
  }

  if (message == WM_CLOSE || 
    (message == WM_KEYDOWN && wParam==VK_ESCAPE) )
	{
    PostQuitMessage(0);
    return 0 ;
	}

  if (message == WM_GETMINMAXINFO) {
    auto & minmax = *reinterpret_cast<MINMAXINFO *>(lParam);
    minmax.ptMinTrackSize.x = 640;
    minmax.ptMinTrackSize.y = 480;
    return 0;
  }

  return DefWindowProc(window, message, wParam, lParam);
}
