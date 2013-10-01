#ifndef GAMEERROR
#define GAMEERROR(name, flag, message)
#endif

GAMEERROR(OutOfTLS, WinAPIError, "Failed to allocate TLS index.")
GAMEERROR(OutOfMemory, WinAPIError, "Out of memory.")

GAMEERROR(WindowClassRegistration, WinAPIError, "Window Class not registred.")
GAMEERROR(WindowCreation, WinAPIError, "Window not create.")

GAMEERROR(GLFunctionInitialization, WinAPIError, "OpenGL function not initialized")