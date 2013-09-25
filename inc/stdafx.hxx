#pragma once

#define STRING(str) #str

#define thread_local __declspec(thread) static

#include <Assert.h>
#include <TChar.h>
#include <StdLib.h>
#include <String.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glcorearb.h>

#include "utils.hxx"

