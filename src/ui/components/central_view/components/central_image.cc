//
// Created by huhua on 2021/11/7.
//

#include "central_image.h"
#include <iostream>
#include <QMouseEvent>

CentralImage::CentralImage(QWidget *parent): QLabel(parent) {

}

void CentralImage::mouseMoveEvent(QMouseEvent *ev) {
    QLabel::mouseMoveEvent(ev);
    std::cout << "ev: " << ev->x() << ", " << ev->y() << std::endl;
}
