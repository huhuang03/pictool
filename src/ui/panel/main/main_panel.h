//
// Created by huhua on 2021/10/12.
//

#ifndef PICTOOL_CENTRAL_VIEW_H
#define PICTOOL_CENTRAL_VIEW_H

#include <opencv2/opencv.hpp>
#include <QWidget>
#include <QLabel>
#include <QLabel>
#include <functional>
#include <QToolButton>
#include "center_image_view.h"
#include "./graphic_image_view.h"

typedef std::function<void (cv::InputArray in, cv::OutputArray out)> ImgAlerter;


/**
 * Can we just just show the image for now.
 */
class MainPanel : public QWidget {
  Q_OBJECT;
private slots:
  void onImgMonthMove(QPoint pos, cv::Vec3b color);
  void updateHistoryUI();

public:
  explicit MainPanel(QWidget *parent = nullptr);

  void loadImage(cv::Mat pImg, bool clear = false);

  /**
   * @return 获取截取的区间
   */
  QRect getCropRegion();

private:
  QLabel *lbStatus;
  QToolButton *btPre;
  QToolButton *btNext;
  GraphicImageView *centerImage;

  void initToolLayout(QLayout *parentLayout);
};


#endif //PICTOOL_CENTRAL_VIEW_H
