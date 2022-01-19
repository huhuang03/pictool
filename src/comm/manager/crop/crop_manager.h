//
// Created by hwf on 2022/1/11.
//

#ifndef PICTOOL_SRC_COMM_CROP_CROP_MANAGER_H_
#define PICTOOL_SRC_COMM_CROP_CROP_MANAGER_H_
#include <opencv2/core.hpp>
#include <vector>

/**
 * 模仿matplot的剪切功能
 */
class CropManager {
 private:
  cv::Mat _src;
  std::vector<cv::Rect> _crops;

 public:
  bool canForward();

  bool canBackward();

  /**
   * clear the crops.
   */
  cv::Mat clear();

  /**
   * get current img;
   */
  cv::Mat img();

  cv::Mat forward();
  cv::Mat backward();

  cv::Mat crop(cv::Rect rect);
};

#endif //PICTOOL_SRC_COMM_CROP_CROP_MANAGER_H_
