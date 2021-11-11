//
// Created by huhua on 2021/11/7.
//

#include "central_image.h"
#include <iostream>
#include <QMouseEvent>

// can I set you fixed size but scale the content with scroll??
CentralImage::CentralImage(QWidget *parent): QLabel(parent) {
    setMouseTracking(true);
    setScaledContents(true);
    this->scale = 1.0;
    this->isDragging = false;
    // ok, we now simple the most scale range is 0 - 5;
}

void CentralImage::mouseMoveEvent(QMouseEvent *ev) {
    QLabel::mouseMoveEvent(ev);
    if (this->isDragging) {
    } else {
        std::cout << "ev: " << ev->x() << ", " << ev->y() << std::endl;
    }
//    if (this->hasFocus()) {
//    }
}

void CentralImage::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    int y = event->angleDelta().y();

    // seems will stock when scroll too big.
    // I want to crop the image??
    if (y != 0) {
        auto isBigger = y < 0;

        // width: 812, height: 663
        // now let's try to get a size.
        auto width = this->size().width();
        auto height = this->size().height();

        if (isBigger) {
            scale = 1.2;
        } else {
            scale = 1 / 1.2;
        }

        // let try scale??
        this->resize(width * scale, height * scale);

        // seems will stock when scroll too big.
        std::cout << "width: " << width << ", height: " << height << std::endl;
    }
}

void CentralImage::mousePressEvent(QMouseEvent *ev) {
    QLabel::mousePressEvent(ev);
    this->isDragging = true;
    this->dragStartPoint = ev->pos();
}

void CentralImage::mouseReleaseEvent(QMouseEvent *ev) {
    QLabel::mouseReleaseEvent(ev);
    this->isDragging = false;
    // ok get the region
}

