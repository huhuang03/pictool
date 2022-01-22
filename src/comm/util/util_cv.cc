//
// Created by hwf on 2022/1/19.
//

#include "pictool/internal/util/util_cv.h"
#include <exception>
#include <opencv2/imgproc.hpp>

void QImage2Mat(const QImage &src, const cv::_OutputArray &out) {
  int format;
  switch (src.format()) {
    case QImage::Format_RGB888:
    case QImage::Format_BGR888:
      format = CV_8UC3;
      break;
    case QImage::Format_ARGB32:
      format = CV_8UC4;
      break;
    default:
      throw std::exception(("UnSupport src format: " + std::to_string(src.format())).c_str());
  }
  cv::Mat share(src.height(), src.width(), format, (void *)src.bits(), src.bytesPerLine());
  if (src.format() == QImage::Format_RGB888) {
    cv::cvtColor(share, share, cv::COLOR_RGB2BGR);
  }

  share.copyTo(out);
}

bool QPointInMat(const cv::Mat &img, QPoint point) {
  return (point.x() >= 0 && point.x() < img.cols) &&
    (point.y() >= 0 && point.y() < img.rows);
}
