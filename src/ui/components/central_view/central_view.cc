//
// Created by huhua on 2021/10/12.
//

#include "central_view.h"
#include <QLayout>
#include <utility>
#include <QDebug>
#include <QScrollArea>
#include "../../../module/size_config.h"
#include "./components/check_state_button.h"
#include <pic_tool/global.h>
#include "../../app.h"

// how to present the global thing?
// recycle import is ok??
CentralView::CentralView(QWidget *parent): QWidget(parent)
, uiImg(new CentralImage()) {

    // so you can auto resize??
    auto scrollArea = new QScrollArea();
    scrollArea->setWidget(uiImg);
    uiImg->resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);
    // so the size is not enough??
    int extraPadding = 30;
    scrollArea->setFixedSize(SIZE_IMG_AREA_W + extraPadding, SIZE_IMG_AREA_H + extraPadding);

    auto rootLayout = new QVBoxLayout();
    this->setLayout(rootLayout);

    rootLayout->addWidget(scrollArea);
    this->initToolLayout(rootLayout);
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

void CentralView::initToolLayout(QLayout *parentLayout) {
    auto container = new QWidget();
    auto layoutTools = new QHBoxLayout(container);
    if (App::awesome == nullptr) {
        App::awesome = new QtAwesome(this);
        App::awesome->initFontAwesome();
    }

    auto btCrop = new CheckStateButton(App::awesome->icon(fa::crop), "Hello");
    layoutTools->addWidget(btCrop);

    layoutTools->addWidget(new QPushButton(App::awesome->icon(fa::crop), "hello 2"));

    layoutTools->addWidget(new QPushButton("hello 1"));

    parentLayout->addWidget(container);
}
