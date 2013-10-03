#include "stdafx.hxx"
#include "sys/application.hxx"

#include "sys/time.hxx"
#include "sys/window.hxx"

inline void * operator new(size_t /*size*/, void * arena){ return (arena); }
inline void operator delete(void * /*address*/, void * /*arena*/) { return; }

application & application::instance()
{
  static unsigned int ID = TlsAlloc();
  if (TLS_OUT_OF_INDEXES == ID) Raise(error::OutOfTLS);

  auto storage = TlsGetValue(ID);
  if (nullptr == storage) {
    storage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(application));
    if (nullptr == storage) Raise(error::OutOfMemory);

    new (storage) application;

    TlsSetValue(ID, storage);
  }

  return *static_cast<application *>(storage);
}

application::application(void) {}

int application::run(void)
{
  extern void render(void);
  extern void update(void);

  createWindow();

  MSG msg = { 0 };
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
      DispatchMessage(&msg);
    else {
      render();
      update();
      SwapBuffers(wglGetCurrentDC());
    }
  }
  return EXIT_SUCCESS;
}
