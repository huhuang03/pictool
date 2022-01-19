//
// Created by huhua on 2021/8/20.
//

#include "util.h"
#include <Windows.h>

unsigned long ms() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
    return time_ms;
}
