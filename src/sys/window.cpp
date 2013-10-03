#include "stdafx.hxx"
#include "sys/window.hxx"
#include "sys/context.hxx"

static ATOM             registerClass(void);
static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

void createWindow(void)
{
  static ATOM classAtom = registerClass();

  DWORD const style = WS_CLIPCHILDREN | WS_CLIPCHILDREN | WS_POPUP,
    styleEx = WS_EX_APPWINDOW;

  auto window = CreateWindowEx(styleEx, MAKEINTRESOURCE(classAtom), TEXT("64k_game"), style,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               nullptr, nullptr, THIS_INSTANCE, nullptr);
  if (!window) Raise(error::WindowCreation);

  glClear(GL_COLOR_BUFFER_BIT);
  SwapBuffers(wglGetCurrentDC());

  ShowWindow(window, SW_SHOWMAXIMIZED);
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
  if (!classAtom) Raise(error::WindowClassRegistration);
  return classAtom;
}

LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  extern void init(void);

  switch (message) {
  case WM_CREATE:
    createContext(window);
    init();
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
