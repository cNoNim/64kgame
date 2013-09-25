#include "stdafx.hxx"
#include "utils.hxx"

void Error(TCHAR const * message) {
  MessageBox(nullptr, message, TEXT("Error!"), MB_ICONERROR | MB_OK);
  ExitProcess( EXIT_FAILURE );
}

void Info(TCHAR const * message) {
  MessageBox(nullptr, message, TEXT("Info!"), MB_ICONINFORMATION | MB_OK);
}

bool YesNo(TCHAR const * message) {
  return MessageBox(nullptr, message, TEXT("Question?"), MB_ICONQUESTION | MB_YESNO) == IDYES;
}