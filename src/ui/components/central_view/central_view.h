//
// Created by huhua on 2021/10/12.
//

#ifndef PICTOOL_CENTRAL_VIEW_H
#define PICTOOL_CENTRAL_VIEW_H

#include <opencv2/opencv.hpp>
#include <QWidget>
#include <QLabel>
#include <functional>
#include "./components/central_image.h"

typedef std::function<void (cv::InputArray in, cv::OutputArray out)> ImgAlerter;


/**
 * Can we just just show the image for now.
 */
class CentralView : public QWidget {
    Q_OBJECT

public:
    explicit CentralView(QWidget *parent = nullptr);

    void loadImage(cv::Mat pImg);

    void addImgAlter(ImgAlerter alerter);

    void updateImg();

private:
    cv::Mat originImg;
    QImage *qImg;
    CentralImage *uiImg;
    std::vector<ImgAlerter> alters;

    void initToolLayout(QLayout *parentLayout);
};


#endif //PICTOOL_CENTRAL_VIEW_H
