//
// Created by huhua on 2021/10/8.
//

#include "hsv_filter_view.h"
#include <easybot/easybot.h>
#include <string>

static RangeSlider* createRangeSlider(QLayout *layout, int min, int max, const QString& title) {
    auto container = new QWidget();
    auto cLayout = new QHBoxLayout(container);
    auto label = new QLabel(title);
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    cLayout->addWidget(label);

    auto rst = new RangeSlider();
    rst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    rst->SetRange(min, max);
    cLayout->addWidget(rst);

    layout->addWidget(container);
    return rst;
}

HSVFilterView::HSVFilterView(QWidget *parent)
    : QWidget(parent) {
    // 不能这么干吗？
    // 因为this还没有初始化完成，所以不能使用引用&this->h?
    auto *layout = new QVBoxLayout(this);
    this->h = createRangeSlider(layout, eb::HSV::H_MIN, eb::HSV::H_MAX, "h: ");
    this->h->SetCanOver(true);
    this->s = createRangeSlider(layout, eb::HSV::S_MIN, eb::HSV::S_MAX, "s: ");
    this->v = createRangeSlider(layout, eb::HSV::V_MIN, eb::HSV::V_MAX, "v: ");

//    layout->addWidget(this->h);
//    layout->addWidget(this->s);
//    layout->addWidget(this->v);
}