#include "stdafx.hxx"
#include "sys/application.hxx"

//EXTERN_C INT _fltused = 0;

void
entrypoint(void)
{
  ExitProcess(application::instance().run());
}

_CRTIMP double  __cdecl _hypot(_In_ double _X, _In_ double _Y)
{
  double ax = fabs(_X), ay = fabs(_Y);
  double xy = _X / _Y, yx = _Y / _X;
  return ax > ay
    ? ax * sqrt(1.0 + yx*yx)
    : ay * sqrt(1.0 + xy*xy);
}