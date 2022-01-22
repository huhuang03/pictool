//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_UTIL_H
#define PIC_TOOL_UTIL_H
#include <stack>
#include <QRectF>

namespace pt {
  unsigned long ms();

  // why not work?
  inline void clear(std::stack<QRectF> &s) {
    std::stack<QRectF> empty;
    s.swap(empty);
  }
}
#endif //PIC_TOOL_UTIL_H
