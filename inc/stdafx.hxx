#pragma once

#include <Assert.h>
#include <TChar.h>
#include <StdLib.h>
#include <String.h>

#define WIN32_LEAN_AND_MEAN 1
#define WIN32_EXTRA_LEAN 1
#include <Windows.h>
#include <WindowsX.h>
#include <UxTheme.h>
#include <DWMApi.h>
#include <GL/GL.h>
#include <GL/wglext.h>
#include <GL/glcorearb.h>

#include <GLM/GLM.hpp>

#define STRING(string) #string

#define RECTWIDTH(rect) (rect.right - rect.left)
#define RECTHEIGHT(rect) (rect.bottom - rect.top)

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define THIS_INSTANCE (reinterpret_cast<HINSTANCE>(&__ImageBase))

#include "sys/core.hxx"
#include "sys/error.hxx"


