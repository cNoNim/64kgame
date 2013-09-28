#pragma once

namespace game
{
  namespace error
  {
    enum class ID 
    {
#define GAMEERROR(name,flag,message) \
      name,
#include "sys/error.inc"
#undef GAMEERROR
      count
    };

    enum FLAG
    {
      UnknownError = 0,
      WinAPIError  = 1<<0
    };

    struct error
    {
      ID index;
      FLAG flag;
#ifndef NDEBUG
      LPCTSTR message;
#endif

      void raise(
#ifndef NDEBUG
        LPCTSTR file,
        LPCTSTR function,
        size_t  line
#endif
        );
    };

#define GAMEERROR(name, flag, message) \
  extern error name;
#include "sys/error.inc"
#undef GAMEERROR
  }
}

#ifndef NDEBUG
#define Raise(error) \
  error.raise(TEXT(__FILE__), TEXT(__FUNCTION__), __LINE__)
#else
#define Raise(error) \
  error.raise()
#endif