//
// Created by huhua on 2021/10/8.
//

#ifndef PIC_TOOL_HSV_FILTER_VIEW_H
#define PIC_TOOL_HSV_FILTER_VIEW_H
#include <QtWidgets>
#include <QWidget>
#include "../range-slider/RangeSlider.h"

class HSVFilterView: public QWidget {
    Q_OBJECT
public:
    HSVFilterView( QWidget* aParent = Q_NULLPTR);

private:
    RangeSlider* h;
    RangeSlider* s;
    RangeSlider* v;
};


#endif //PIC_TOOL_HSV_FILTER_VIEW_H
