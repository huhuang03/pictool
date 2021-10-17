//
// Created by huhua on 2021/10/8.
//

#ifndef PIC_TOOL_HSV_FILTER_VIEW_H
#define PIC_TOOL_HSV_FILTER_VIEW_H
#include <QtWidgets>
#include <QWidget>
#include "../range-slider/RangeSlider.h"
#include <easybot/model/hsv_range.h>

class HSVFilterView: public QWidget {
    Q_OBJECT
public:
    HSVFilterView(QWidget* aParent = Q_NULLPTR);
    eb::HSVRange range();

    signals:
    void hsvRangeChange(eb::HSVRange range);

public slots:
    void handleSingleHSVChanged(int lower, int upper);

private:
    RangeSlider* h;
    RangeSlider* s;
    RangeSlider* v;

    // helper method
private:
    RangeSlider* createRangeSlider(QLayout *layout, int min, int max, const QString& title);
};


#endif //PIC_TOOL_HSV_FILTER_VIEW_H
