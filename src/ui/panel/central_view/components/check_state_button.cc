//
// Created by huhua on 2021/11/10.
//

#include "check_state_button.h"
CheckStateButton::CheckStateButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text,
                                                                                                          parent) {
    // ok, let's try set backgroundColor
    QPalette pal = this->palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->update();
}

CheckStateButton::CheckStateButton(const QIcon &icon, QWidget *parent): CheckStateButton(icon, "", parent) {

}
