//
// Created by th on 2022/1/30.
//

#ifndef PICTOOL_SRC_UI_PANEL_HSV_COMPONENTS_HSV_FILTER_ITEM_VIEW_H_
#define PICTOOL_SRC_UI_PANEL_HSV_COMPONENTS_HSV_FILTER_ITEM_VIEW_H_

#include <QWidget>
#include <string>
#include <QLabel>
#include "../../../../components/range-slider/RangeSlider.h"

class HsvFilterItemView: public QWidget {
  Q_OBJECT
 public:
  signals:
  void onChange(int lower, int upper);

 public:
  HsvFilterItemView(const std::string &title, int min, int max);

 public:
  RangeSlider *getRangerSlider();

 private:
  QLabel *label;
  std::string title;
  RangeSlider *rs;
  void updateLabel(int lower, int upper);

 private slots:
  void handleChange(int lower, int upper);

};

#endif //PICTOOL_SRC_UI_PANEL_HSV_COMPONENTS_HSV_FILTER_ITEM_VIEW_H_
