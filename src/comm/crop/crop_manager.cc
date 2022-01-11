//
// Created by hwf on 2022/1/11.
//

#include "crop_manager.h"
cv::Mat CropManager::img() {
  // ok, this is something important
  cv::Mat rst = _src;
  for (const auto &crop: this->_crops) {
    rst = rst(crop);
  }
  return rst;
}
bool CropManager::canForward() {
  return false;
}
