//
// Created by huhua on 2021/8/20.
//

#include <pictool/internal/util.h>
#include <Windows.h>

namespace pt {
unsigned long ms() {
  SYSTEMTIME time;
  GetSystemTime(&time);
  LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
  return time_ms;
}

//template<class T>
//void clear(std::stack<T> &s) {
//  std::stack<T> empty;
//  s.swap(empty);
//}
}
