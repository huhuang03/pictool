//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_UTIL_H
#define PIC_TOOL_UTIL_H
#include <stack>

namespace pt {
unsigned long ms();
template <class T>
void clear(std::stack<T> &s);
}
#endif //PIC_TOOL_UTIL_H
