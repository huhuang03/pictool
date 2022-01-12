//
// Created by huhua on 2021/10/12.
//

#include "main_panel.h"
#include <QLayout>
#include <utility>
#include <QDebug>
#include <QScrollArea>
#include "../../../module/size_config.h"
#include "../central_view/components/check_state_button.h"
#include "pic_tool/global.h"
#include "../../app.h"
#include <QToolButton>

// how to present the global thing?
// recycle import is ok??
MainPanel::MainPanel(QWidget *parent): QWidget(parent)
//, centerImage(new CenterImageView()) {
, centerImage(new GraphicImageView()) {

    // so you can auto resize??
//    auto scrollArea = new QScrollArea();
//    scrollArea->setWidget(centerImage);
    centerImage->resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);
    // so the size is not enough??
//    scrollArea->setFixedSize(SIZE_IMG_AREA_W + extraPadding, SIZE_IMG_AREA_H + extraPadding);

    auto rootLayout = new QVBoxLayout();
    this->setLayout(rootLayout);

    rootLayout->addWidget(centerImage);
    this->initToolLayout(rootLayout);
}

void MainPanel::loadImage(cv::Mat img) {
    this->originImg = std::move(img);
    this->updateImg();
}

void MainPanel::addImgAlter(ImgAlerter alerter) {
    this->alters.push_back(alerter);
}

void MainPanel::updateImg() {
    if (this->originImg.empty()) {
        return;
    }

    cv::Mat curImg = this->originImg;
    for (const auto &alter: this->alters) {
        cv::Mat outImg;
        alter(curImg, outImg);
        curImg = outImg;
    }

    this->centerImage->setPixmap(QPixmap::fromImage(QImage((unsigned char*) curImg.data, curImg.cols, curImg.rows, QImage::Format_BGR888)));
}

void MainPanel::initToolLayout(QLayout *parentLayout) {
    auto container = new QWidget();
    auto layoutTools = new QHBoxLayout(container);
    if (App::awesome == nullptr) {
        App::awesome = new QtAwesome(this);
        App::awesome->initFontAwesome();
    }

    // how to set the
    auto btCrop1 = new QToolButton();
    btCrop1->setIcon(App::awesome->icon(fa::search));
    btCrop1->setCheckable(true);
    layoutTools->addWidget(btCrop1);

    parentLayout->addWidget(container);
}
