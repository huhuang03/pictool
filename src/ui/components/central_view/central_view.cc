//
// Created by huhua on 2021/10/12.
//

#include "central_view.h"
#include <QLayout>
#include <utility>
#include <QDebug>
#include <QScrollArea>
#include "../../../module/size_config.h"

static const int WIDTH = 800;
static const int HEIGHT = 600;

CentralView::CentralView(QWidget *parent): QWidget(parent)
, uiImg(new CentralImage()) {
    resize(WIDTH, HEIGHT);
    // so you can auto resize??
    auto scrollArea = new QScrollArea();
    scrollArea->setWidget(uiImg);
    uiImg->resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);
    scrollArea->setFixedSize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);

    auto layout = new QVBoxLayout();
    this->setLayout(layout);

    layout->addWidget(scrollArea);

    // add the op button like cv plot.
}

void CentralView::loadImage(cv::Mat img) {
    this->originImg = std::move(img);
    this->updateImg();
}

void CentralView::addImgAlter(ImgAlerter alerter) {
    this->alters.push_back(alerter);
}

void CentralView::updateImg() {
    if (this->originImg.empty()) {
        return;
    }

    cv::Mat curImg = this->originImg;
    for (const auto &alter: this->alters) {
        cv::Mat outImg;
        alter(curImg, outImg);
        curImg = outImg;
    }

    this->uiImg->setPixmap(QPixmap::fromImage(QImage((unsigned char*) curImg.data, curImg.cols, curImg.rows, QImage::Format_BGR888)));
}