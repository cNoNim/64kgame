#include "stdafx.hxx"
#include "sys/time.hxx"

glm::int64_t ticks(void)
{
  const double ticks_per_second = 10000000.0;
  static LARGE_INTEGER freq;
  static glm::uint64_t start_time;

  LARGE_INTEGER value;
  QueryPerformanceCounter(&value);
  
  if (!freq.QuadPart) {
    QueryPerformanceFrequency(&freq);
    start_time = value.QuadPart;
  }
  
  glm::uint64_t current_time = value.QuadPart;

  return glm::int64_t((current_time - start_time) * ticks_per_second / freq.QuadPart);
}