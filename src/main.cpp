#include <CType.h>
#include <Locale.h>
#include <Malloc.h>
#include <StdLib.h>
#include <String.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define stack_alloc(type, count) reinterpret_cast<type *>(_malloca(sizeof(type)*(count)))
#define stack_free(data) _freea(data)

static void UnEscapeQuotes  (char *arg);
static int  ParseCommandLine(char *cmdline, char **argv);
static void ShowError       (const char *title, const char *message);
static int  OutOfMemory     (void);

namespace game
{
  HINSTANCE instance;
  int show;

  int 
  main(int argc, char *argv[])
  {
    MessageBox(NULL, "Hello, World!", "Hello", MB_ICONASTERISK | MB_OK);
    return EXIT_SUCCESS;
  }
}


int 
main(int argc, char *argv[])
{
  auto status = game::main(argc, argv);
  exit(status);
  return 0;
}

int WINAPI
WinMain(HINSTANCE instance, HINSTANCE prevInstance, char * cmdLine, int show)
{
  UNREFERENCED_PARAMETER(prevInstance);

  game::instance = instance;
  game::show = show;

  auto text_length = strlen(cmdLine) + 1;
  auto cmdline = stack_alloc(char, text_length);
  if (cmdline == NULL) return OutOfMemory();
  strcpy_s(cmdline, sizeof(char) * text_length, cmdLine);
  
  auto argc = ParseCommandLine(cmdline, NULL);
  auto argv = stack_alloc(char *, argc + 1); 
  if (argv == NULL) return OutOfMemory(); 
  ParseCommandLine(cmdline, argv);
  
  auto status = game::main(argc, argv);
  
  stack_free(argv);
  stack_free(cmdline);
  
  exit(status);
  return 0;
}

static void
UnEscapeQuotes(char *arg)
{
  char *last = nullptr;
  
  for (;*arg; ++arg) {
    if (*arg == '"' && (last != NULL && *last == '\\')) {
      char *c_curr = arg;
      char *c_last = last;
      
      for (; *c_curr; 
        ++c_curr) {
        *c_last = *c_curr;
        c_last = c_curr;
      }
      
      *c_last = '\0';
    }
    
    last = arg;
  }
}

static int
ParseCommandLine(char *cmdline, char **argv)
{
  char *lastp = nullptr;
  int argc = 0, last_argc = 0;
  for (auto bufp = cmdline; *bufp;) {
    while (isspace(*bufp))
      ++bufp;

    if (*bufp == '"') {
      ++bufp;
      if (*bufp) {
        if (argv) 
          argv[argc] = bufp;

        ++argc;
      }

      lastp = bufp;
      for(;*bufp && (*bufp != '"' || *lastp == '\\');
        ++bufp) {
        lastp = bufp;
      }
    } else {
      if (*bufp) {
        if (argv)
          argv[argc] = bufp;

        ++argc;
      }

      for(;*bufp && !isspace(*bufp); ++bufp);
    }
    if (*bufp) { 
      if (argv)
        *bufp = '\0';
      
      ++bufp;
    }
    
    if (argv && last_argc != argc)
      UnEscapeQuotes(argv[last_argc]);

    last_argc = argc;
  }
  if (argv)
    argv[argc] = nullptr;

  return (argc);
}


static void 
ShowError(const char *title, const char *message)
{
  MessageBox(nullptr, message, title, MB_ICONEXCLAMATION | MB_OK);
}

static int 
OutOfMemory(void)
{
  ShowError("Fatal Error", "Out of memory - aborting");
  return EXIT_FAILURE;
}
