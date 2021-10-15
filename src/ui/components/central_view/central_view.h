//
// Created by huhua on 2021/10/12.
//

#ifndef PICTOOL_CENTRAL_VIEW_H
#define PICTOOL_CENTRAL_VIEW_H

#include <opencv2/opencv.hpp>
#include <QWidget>
#include <QLabel>

/**
 * Can we just just show the image for now.
 */
class CentralView : public QWidget{
    Q_OBJECT

public:
    explicit CentralView(QWidget *parent = nullptr);

    void loadImage(cv::Mat pImg);

private:
    cv::Mat cvImg;
    QImage *qImg;
    QLabel *label;
};


#endif //PICTOOL_CENTRAL_VIEW_H
