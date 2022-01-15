//
// Created by huhua on 2022/1/15.
//

#include <opencv2/imgproc.hpp>
#include "util.h"

void qImage2Mat(const QImage &img, const cv::_OutputArray &out) {
    cv::Mat mat;
    switch(img.format())
    {
        case QImage::Format_ARGB32:
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(img.height(), img.width(), CV_8UC4, (void*)img.constBits(), img.bytesPerLine());
            break;
        case QImage::Format_RGB888:
            mat = cv::Mat(img.height(), img.width(), CV_8UC3, (void*)img.constBits(), img.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
            break;
        case QImage::Format_Indexed8:
            mat = cv::Mat(img.height(), img.width(), CV_8UC1, (void*)img.constBits(), img.bytesPerLine());
            break;
        default:
            throw "Should not happen";
    }
    mat.copyTo(out);
}
