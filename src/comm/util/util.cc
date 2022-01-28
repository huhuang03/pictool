//
// Created by huhua on 2021/8/20.
//

#include <pictool/internal/util.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#endif

namespace pt {
unsigned long ms() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  SYSTEMTIME time;
  GetSystemTime(&time);
  LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
  return time_ms;
#endif
  return 0;
}

}
