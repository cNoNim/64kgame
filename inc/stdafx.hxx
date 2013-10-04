#pragma once

#define _HAS_EXCEPTIONS 0

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

#include <GLM/GLM.hpp>

#define noexcept throw ()
#define constexpr

#define STRING(string) #string

#define RECTWIDTH(rect) (rect.right - rect.left)
#define RECTHEIGHT(rect) (rect.bottom - rect.top)

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define THIS_INSTANCE (reinterpret_cast<HINSTANCE>(&__ImageBase))

#include "sys/error.hxx"

#include "core/array"

#include "resources.hxx"