//
// Created by huhua on 2021/10/16.
//

#ifndef PICTOOL_SETTING_H
#define PICTOOL_SETTING_H
#include <iostream>
#include <QWidget>

void settingInit(QWidget* widget);

std::string settingGet(const std::string& key, const std::string& fallback);
void settingSet(const std::string& key, const std::string& value);
#endif //PICTOOL_SETTING_H
