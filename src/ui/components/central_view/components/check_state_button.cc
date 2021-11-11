//
// Created by huhua on 2021/11/10.
//

#include "check_state_button.h"
CheckStateButton::CheckStateButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text,
                                                                                                          parent) {

}

CheckStateButton::CheckStateButton(const QIcon &icon, QWidget *parent): CheckStateButton(icon, "", parent) {

}
