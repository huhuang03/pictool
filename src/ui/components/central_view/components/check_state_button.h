//
// Created by huhua on 2021/11/10.
//

#ifndef PICTOOL_CHECK_STATE_BUTTON_H
#define PICTOOL_CHECK_STATE_BUTTON_H

#include <QPushButton>

class CheckStateButton: public QPushButton {
    Q_OBJECT;
public:
    explicit CheckStateButton(const QIcon& icon, QWidget *parent = nullptr);

    // Icon?
    CheckStateButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
};


#endif //PICTOOL_CHECK_STATE_BUTTON_H
