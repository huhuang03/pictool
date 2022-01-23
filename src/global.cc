//
// Created by huhua on 2022/1/22.
//
#include <pictool/internal/global.h>

static QSettings* settingCache = nullptr;

QSettings *getSetting() {
  if (settingCache == nullptr) {
    settingCache = new QSettings("Th", "PicTool");
  }
  return settingCache;
}
