#pragma once

namespace game
{
  class app
  {
  public:
    app(HINSTANCE instance);
    ~app(void) { }

    int 
    run(void);
    void
    tick(void);
  private:
    HINSTANCE instance;
    HWND window;
    HDC device;
    HGLRC context;
    bool fullscreen;
  };
}

