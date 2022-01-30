//
// Created by huhua on 2021/10/8.
//

#ifndef PIC_TOOL_HSV_FILTER_VIEW_H
#define PIC_TOOL_HSV_FILTER_VIEW_H
#include <QtWidgets>
#include <QWidget>
#include "../../../components/range-slider/RangeSlider.h"
#include <easybot/model/hsv_range.h>
#include "./components/hsv_filter_item_view.h"
#include <string>

class HSVFilterView : public QWidget {
 Q_OBJECT
 public:
  HSVFilterView(QWidget *aParent = Q_NULLPTR);
  eb::HSVRange range();

 signals:
  void hsvRangeChange(eb::HSVRange range);

 public slots:
  void handleSingleHSVChanged(int lower, int upper);

 private:
  HsvFilterItemView *h;
  HsvFilterItemView *s;
  HsvFilterItemView *v;
//  RangeSlider *h;
//  RangeSlider *s;
//  RangeSlider *v;
  eb::HSVRange hsvRange;

  // helper method
 private:
  HsvFilterItemView *createRangeSlider(QLayout *layout, int min, int max, const std::string &title);
};

#endif //PIC_TOOL_HSV_FILTER_VIEW_H
