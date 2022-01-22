//
// Created by huhua on 2021/10/12.
//

#include "main_panel.h"
#include <QLayout>
#include <utility>
#include "../../../module/size_config.h"
#include <pictool/global.h>
#include "../../app.h"
#include <QToolButton>

// how to present the global thing?
// recycle import is ok??
MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
//, centerImage(new CenterImageView()) {
    , centerImage(new GraphicImageView()) {
  centerImage->setFixedSize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);

  auto rootLayout = new QVBoxLayout();
  this->setLayout(rootLayout);

  rootLayout->addWidget(centerImage);
  this->initToolLayout(rootLayout);

  connect(centerImage, &GraphicImageView::onMove, this,
          &MainPanel::onImgMonthMove);
  connect(centerImage, &GraphicImageView::onHistoryChange, this, &MainPanel::updateHistoryUI);

  connect(this->btNext, &QToolButton::clicked, centerImage, &GraphicImageView::forward);
  connect(this->btPre, &QToolButton::clicked, centerImage, &GraphicImageView::backward);

  this->updateHistoryUI(); }

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
  for (const auto &alter : this->alters) {
    cv::Mat outImg;
    alter(curImg, outImg);
    curImg = outImg;
  }

  // hwo can I print the image data type?
  this->centerImage->setImage(curImg);
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

  this->btPre = new QToolButton();
  btPre->setIcon(App::awesome->icon(fa::arrowleft));
  layoutTools->addWidget(btPre);

  this->btNext = new QToolButton();
  btNext->setIcon(App::awesome->icon(fa::arrowright));
  layoutTools->addWidget(btNext);

  this->lbStatus = new QLabel();

  layoutTools->addWidget(this->lbStatus);

  parentLayout->addWidget(container);
}


void MainPanel::onImgMonthMove(QPoint pos, cv::Vec3b color) {
//  std::cout << "color: " << color << std::endl;
//  qDebug() << "onImgMonthMove: " << pos << color[0];
  lbStatus->setText(
      QString("[%1,%2](%3,%4,%5)")
          .arg(pos.x())
          .arg(pos.y())
          .arg(color[0])
          .arg(color[1])
          .arg(color[2])
  );
}

void MainPanel::updateHistoryUI() {
  this->btNext->setEnabled(this->centerImage->canForward());
  this->btPre->setEnabled(this->centerImage->canBackward());
}
