#include "stdafx.hxx"
#include "game.hxx"

#include <new.h>

static void * create_window(wchar_t const * name);
static LRESULT CALLBACK window_proc( HWND window, UINT message, WPARAM wParam, LPARAM lParam);

static LRESULT on_create(HWND window);
static LRESULT on_hittest(HWND window, int x, int y);

namespace game
{
  static void init(application & app);
  static void tick(application & app);

  application & application::instance() {
    static unsigned int ID = TlsAlloc();
    if (TLS_OUT_OF_INDEXES == ID) Raise(error::OutOfTLS);

    auto storage = TlsGetValue(ID);
    if (nullptr == storage) {
      storage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(application));
      if (nullptr == storage) Raise(error::OutOfMemory);

      new (storage) game::application;

      TlsSetValue(ID, storage);
    }
    
    return *static_cast<game::application *>(storage);
  }

  application::application(void)
  {
    create_window(TEXT("x64_game"));
    gl.init();
  }

  int 
  application::run(void)
  {
    MSG msg = { 0 };
    init(*this);
    while(msg.message != WM_QUIT)
    {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        DispatchMessage(&msg);
      else {
        tick(*this);
        SwapBuffers(wglGetCurrentDC());
      }
    }
    return EXIT_SUCCESS;
  }

  inline void
  init(application & /*app*/)
  {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  }

  inline void 
  tick(application & /*app*/)
  {
    glClear( GL_COLOR_BUFFER_BIT );
  }
}

void * create_window(wchar_t const * name)
{
  static ATOM window_class = 0;
  if (0 == window_class) {
      WNDCLASS wc = { 0 };

      wc.style = CS_OWNDC;
      wc.lpfnWndProc = window_proc;
      wc.hInstance = THIS_INSTANCE;
      wc.lpszClassName = name;

      window_class = RegisterClass(&wc);
      if (0 == window_class) Raise(game::error::WindowClassRegistration);
  }

  unsigned long const styleEx = WS_EX_APPWINDOW, style = WS_VISIBLE | WS_SIZEBOX | WS_POPUP;
  auto handle = CreateWindowEx(styleEx, name, name, style,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    nullptr, nullptr, THIS_INSTANCE, nullptr);
  if (!handle) Raise(game::error::WindowCreation);
  return handle;
}

LRESULT CALLBACK
window_proc( HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_CREATE)
    return on_create(window);

  if (message == WM_ACTIVATE) {
    MARGINS margins = { 0 };
    DwmExtendFrameIntoClientArea(window, &margins);
    return 0;
  }

  if ((message == WM_NCCALCSIZE) && (wParam == TRUE)) {
    return 0;
  }

  if (message == WM_NCHITTEST) {
    return on_hittest(window, wParam, lParam);
  }

  if ( message == WM_CLOSE 
    || (message == WM_KEYDOWN && wParam==VK_ESCAPE) )
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

LRESULT
on_create(HWND window) 
{
  // Create OpenGL context
  static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    24, 0, 0, 0, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0,
    32,
    0,
    0,
    PFD_MAIN_PLANE,
    0, 0, 0, 0
  };

  auto device = GetDC(window); 
  auto format = ChoosePixelFormat(device, &pfd);
  SetPixelFormat(device, format, &pfd);
    
  auto rc = wglCreateContext(device);
  wglMakeCurrent(device, rc);

  // ...
  RECT rect;
  GetWindowRect(window, &rect);

  SetWindowPos(window, 
    NULL, 
    rect.left, rect.top,
    RECTWIDTH(rect), RECTHEIGHT(rect),
    SWP_FRAMECHANGED);  

  return 0;
}

LRESULT 
on_hittest(HWND window, int x, int y) 
{
  RECT windowRect;
  GetWindowRect(window, &windowRect);
  RECT frameRect = { 0 };
  AdjustWindowRectEx(&frameRect, WS_VISIBLE | WS_SIZEBOX | WS_POPUP | WS_CAPTION, FALSE, WS_EX_APPWINDOW);
  
  bool onBorder = false;
  short row = 0, col = 0;

  if ((y >= windowRect.top) 
    && (y < windowRect.top - frameRect.bottom)) {
    onBorder = y < (windowRect.top - frameRect.top);
    row = -1;
  } else if ( (y < windowRect.bottom) 
           && (y >= windowRect.bottom - frameRect.bottom)) {
    row = 1;
  }

  if ( (x >= windowRect.left)
    && (x < windowRect.left - frameRect.left)) {
    col = -1;
  } else if ( (x < windowRect.right)
           && (x >= windowRect.right - frameRect.right)) {
    col = 1;
  }

  LRESULT test[3][3] = {
    { HTTOPLEFT,    onBorder ? HTTOP : HTCAPTION, HTTOPRIGHT    },
    { HTLEFT,       HTNOWHERE,                    HTRIGHT       },
    { HTBOTTOMLEFT, HTBOTTOM,                     HTBOTTOMRIGHT }
  };

  return test[row + 1][col + 1];
}
