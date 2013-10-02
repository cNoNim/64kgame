#include "stdafx.hxx"
#include "sys/error.hxx"

namespace game 
{
  namespace error
  {
#ifndef NDEBUG
#define GAMEERROR(name, flag, message) \
  error name = { ID::name, flag, TEXT(message) };
#else
#define GAMEERROR(name, flag, message) \
  error name = { ID::name, flag };
#endif
#include "sys/error.inc"
#undef GAMEERROR

    void error::raise(
#ifndef NDEBUG
      LPCTSTR file,
      LPCTSTR function,
      size_t  line
#endif
      )
    {
      MessageBeep(MB_ICONERROR);



      ExitProcess(EXIT_FAILURE);
    }
  }
}