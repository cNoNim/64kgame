#pragma once

#define _HAS_EXCEPTIONS 0

#ifndef __has_feature
# define __has_feature(x) 0
#endif

#if __has_feature(cxx_constexpr) 
#else
# if defined(_MSC_VER)
#   define _ALLOW_KEYWORD_MACROS
# endif
# define constexpr
#endif

#if __has_feature(cxx_noexcept)
#else
# if defined(_MSC_VER)
#   define _ALLOW_KEYWORD_MACROS
# endif
# define noexcept throw ()
#endif

#define _WIN32_WINNT 0x0601

#define WIN32_LEAN_AND_MEAN 1
#define WIN32_EXTRA_LEAN 1

#include <TChar.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glcorearb.h>

#include <New>
#include <CAssert>
#include <CStdLib>
#include <CMath>

#define STRING(string) #string

#define RECTWIDTH(rect) (rect.right - rect.left)
#define RECTHEIGHT(rect) (rect.bottom - rect.top)

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define THIS_INSTANCE (reinterpret_cast<HINSTANCE>(&__ImageBase))

#if defined(__clang__)
#undef _MSC_VER
#endif
//#include <GLM/GLM.hpp>

#include "sys/error.hxx"

#include "core/array"

#include "resources.hxx"