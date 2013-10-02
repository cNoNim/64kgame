#ifndef GAMEERROR
#define GAMEERROR(name, flag, message)
#endif

GAMEERROR(CrossThreadAccess, ApplicationError, "Cross thread access to application instance.")

GAMEERROR(OutOfTLS, WinAPIError, "Failed to allocate TLS index.")
GAMEERROR(OutOfMemory, WinAPIError, "Out of memory.")

GAMEERROR(WindowClassRegistration, WinAPIError, "Window Class not registred.")
GAMEERROR(WindowCreation, WinAPIError, "Window not create.")

GAMEERROR(GLFunctionInitialization, WinAPIError, "OpenGL function not initialized")