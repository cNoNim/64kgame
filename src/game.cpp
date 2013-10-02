#include "stdafx.hxx"
#include "game.hxx"

#include <new.h>

static void             createContext(HWND window, game::application & app);
static void             createWindow(game::application & app);
static void             destroyContext(HWND window);
static ATOM             registerClass(void);
static void             updateClipRect(HWND window);
static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

namespace game
{
  static void init(application & app);
  static void tick(application & app);

  application & application::instance()
  {
    static GL gl;
    static WGL wgl;
    static auto mainThread = GetCurrentThread();
    if (GetCurrentThread() != mainThread) Raise(error::CrossThreadAccess);

    static unsigned int ID = TlsAlloc();
    if (TLS_OUT_OF_INDEXES == ID) Raise(error::OutOfTLS);

    auto storage = TlsGetValue(ID);
    if (nullptr == storage) {
      storage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(application));
      if (nullptr == storage) Raise(error::OutOfMemory);

      new (storage) game::application(gl, wgl);

      TlsSetValue(ID, storage);
    }

    return *static_cast<game::application *>(storage);
  }

  application::application(GL & gl, WGL & wgl) :
    gl(gl), wgl(wgl)
  {
    createWindow(*this);
  }

  int application::run(void)
  {
    MSG msg = { 0 };
    init(*this);
    while (msg.message != WM_QUIT) {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        DispatchMessage(&msg);
      else {
        tick(*this);
        SwapBuffers(wglGetCurrentDC());
      }
    }
    return EXIT_SUCCESS;
  }

  inline void init(application & /*app*/)
  {
  }

  inline void tick(application & /*app*/)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  }
}

void createContext(HWND window, game::application & app)
{
  auto & gl = app.gl;
  auto & wgl = app.wgl;

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

void createWindow(game::application & app)
{
  static ATOM classAtom = registerClass();

  DWORD const style = WS_CLIPCHILDREN | WS_CLIPCHILDREN | WS_POPUP,
    styleEx = WS_EX_APPWINDOW;

  auto window = CreateWindowEx(styleEx, MAKEINTRESOURCE(classAtom), TEXT("64k_game"), style,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               nullptr, nullptr, THIS_INSTANCE, &app);
  if (!window) Raise(game::error::WindowCreation);

  glClear(GL_COLOR_BUFFER_BIT);
  SwapBuffers(wglGetCurrentDC());

  ShowWindow(window, SW_SHOWMAXIMIZED);
}

void destroyContext(HWND window)
{
  auto device = wglGetCurrentDC();
  auto rc = wglGetCurrentContext();
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(rc);
  ReleaseDC(window, device);
}

ATOM registerClass(void)
{
  WNDCLASS wc = { 0 };
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = windowProc;
  wc.hInstance = THIS_INSTANCE;
  wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
  wc.lpszClassName = TEXT("64k_game");

  auto classAtom = RegisterClass(&wc);
  if (!classAtom) Raise(game::error::WindowClassRegistration);
  return classAtom;
}

LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
  case WM_CREATE:
    createContext(window, *static_cast<game::application *>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams));
    break;
  case WM_ACTIVATE:
    if (WA_INACTIVE != LOWORD(wParam) && 0 == HIWORD(wParam))
      ShowCursor(FALSE);
    else
      ShowCursor(TRUE);
    return 0;
  case WM_CLOSE:
    destroyContext(window);
    DestroyWindow(window);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_ERASEBKGND:
    return TRUE;
  }
  return DefWindowProc(window, message, wParam, lParam);
}
