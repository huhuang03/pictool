//
// Created by huhua on 2021/8/20.
//

#include "pictool/internal/util/util_eq.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
bool eq(const POINT &p1, const POINT &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}
#endif