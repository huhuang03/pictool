//
// Created by huhua on 2021/10/12.
//

#include "central_view.h"
#include <QLayout>
#include <utility>
#include <QDebug>
#include <QVBoxLayout>

CentralView::CentralView(QWidget *parent): QWidget(parent)
, label(new QLabel) {
    auto layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->addWidget(label);
}

void CentralView::loadImage(cv::Mat img) {
    this->cvImg = std::move(img);
    // why? exception??
    this->label->setPixmap(QPixmap::fromImage(QImage((unsigned char*) this->cvImg.data, this->cvImg.cols, this->cvImg.rows, QImage::Format_BGR888)));
}
