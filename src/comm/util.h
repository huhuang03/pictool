//
// Created by huhua on 2022/1/15.
//

#ifndef PICTOOL_SRC_COMM_UTIL_H_
#define PICTOOL_SRC_COMM_UTIL_H_

#include <QImage>
#include <opencv2/core.hpp>

void qImage2Mat(const QImage &img, cv::OutputArray out);

#endif //PICTOOL_SRC_COMM_UTIL_H_
