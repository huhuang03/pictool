//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_UTIL_EQ_H
#define PIC_TOOL_UTIL_EQ_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>

bool eq(const POINT &p1, const POINT &p2);
#endif

#endif //PIC_TOOL_UTIL_EQ_H
