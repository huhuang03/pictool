//
// Created by huhua on 2021/10/8.
//

#include "hsv_filter_view.h"
#include <QVBoxLayout>
#include <easybot/easybot.h>

static RangeSlider* createRangeSlider(int min, int max) {
    auto rst = new RangeSlider();
    rst->SetRange(min, max);
    return rst;
}

HSVFilterView::HSVFilterView(QWidget *parent)
    : QWidget(parent) {
    this->h = createRangeSlider(eb::HSV::H_MIN, eb::HSV::H_MAX);
    this->s = createRangeSlider(eb::HSV::S_MIN, eb::HSV::S_MAX);
    this->v = createRangeSlider(eb::HSV::V_MIN, eb::HSV::V_MAX);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(this->h);
    layout->addWidget(this->s);
    layout->addWidget(this->v);
}