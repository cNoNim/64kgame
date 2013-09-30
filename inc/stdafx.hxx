#pragma once

#define STRING(string) #string

#include <Assert.h>
#include <TChar.h>
#include <StdLib.h>
#include <String.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>
#include <WindowsX.h>
#include <UxTheme.h>
#include <DWMApi.h>
#include <GL/GL.h>
#include <GL/glcorearb.h>

#include <GLM/GLM.hpp>

#define RECTWIDTH(rect) (rect.right - rect.left)
#define RECTHEIGHT(rect) (rect.bottom - rect.top)

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

#define THIS_INSTANCE (reinterpret_cast<HINSTANCE>(&__ImageBase))

#include "sys/core.hxx"
#include "sys/error.hxx"


