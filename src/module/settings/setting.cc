//
// Created by huhua on 2021/10/16.
//


#include <pictool/settings/setting.h>
#include <QSettings>

static QSettings *qSetting;

void settingInit(QWidget *widget) {
    qSetting = new QSettings("tt", "pic_tool", widget);
}

std::string settingGet(const std::string& key, const std::string& fallback) {
    return qSetting->value(QString::fromUtf8(key.c_str()), QString::fromUtf8(fallback.c_str())).toString().toStdString();
}

void settingSet(const std::string& key, const std::string& value) {
    qSetting->setValue(QString::fromUtf8(key.c_str()), QString::fromUtf8(value.c_str()));
}

