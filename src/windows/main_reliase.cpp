#include "stdafx.hxx"
#include "game.hxx"
#include "new.h"

extern "C" int _fltused = 0;

static DWORD tlsID;

game::app & instance() {
  auto storage = TlsGetValue(tlsID);
  if(nullptr == storage) Error(TEXT("Can't get thread local storage"));
  return *static_cast<game::app *>(storage);
}

void
entrypoint(void)
{
  using namespace game;

  if(TLS_OUT_OF_INDEXES == (tlsID = TlsAlloc())) Error(TEXT("Can't allocate thread local index"));

  auto storage = LocalAlloc(LPTR, sizeof(game::app));

  if(!TlsSetValue(tlsID, storage)) Error(TEXT("Can't set thread local storage"));

  game::app * app = new (storage) game::app(GetModuleHandle(nullptr), YesNo(TEXT("Run in fullscreen?")));

  ExitProcess(app->run());
}
