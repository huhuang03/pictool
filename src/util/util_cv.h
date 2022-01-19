//
// Created by hwf on 2022/1/19.
//

#ifndef PICTOOL_SRC_UTIL_UTIL_CV_H_
#define PICTOOL_SRC_UTIL_UTIL_CV_H_
#include <QImage>
#include <opencv2/core.hpp>

bool QPointInMat(const cv::Mat &img, QPoint point);
void QImage2Mat(const QImage &src, cv::OutputArray out);
#endif //PICTOOL_SRC_UTIL_UTIL_CV_H_
