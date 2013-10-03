#pragma once

#include <TChar.h>
#include <CAssert>
#include <CStdLib>

#include <GLM/GLM.hpp>

#define _WIN32_WINNT 0x0600
#define WIN32_LEAN_AND_MEAN 1
#define WIN32_EXTRA_LEAN 1
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glcorearb.h>

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