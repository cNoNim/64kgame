#include "stdafx.hxx"
#include "sys/application.hxx"

EXTERN_C int _fltused = 0;

void WinMainCRTStartup(void)
{
  ExitProcess(application::instance().run());
}

double _cdecl _hypot(double x, double y)
{
  double ax = fabs(x), ay = fabs(y);
  double xy = x / y, yx = y / x;
  return ax > ay
    ? ax * sqrt(1.0 + yx*yx)
    : ay * sqrt(1.0 + xy*xy);
}