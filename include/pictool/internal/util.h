//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_UTIL_H
#define PIC_TOOL_UTIL_H
#include <stack>
#include <QRectF>
#include "./util/util_cv.h"
#include "./util/util_eq.h"

namespace pt {
  unsigned long ms();

  // why not work?
  inline void clear(std::stack<QRectF> &s) {
    std::stack<QRectF> empty;
    s.swap(empty);
  }

  void blockPrompt(const std::string& msg);
}
#endif //PIC_TOOL_UTIL_H
