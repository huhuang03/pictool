//
// Created by huhua on 2021/10/8.
//

#include "hsv_filter_view.h"
#include <string>

HSVFilterView::HSVFilterView(QWidget *parent)
    : QWidget(parent), hsvRange({0, 0, 0}, {0, 0, 0}) {
  // 不能这么干吗？
  // 因为this还没有初始化完成，所以不能使用引用&this->h?
  auto *layout = new QVBoxLayout(this);
  this->h = createRangeSlider(layout, eb::HSV::H_MIN, eb::HSV::H_MAX, "h: ");
  this->h->getRangerSlider()->SetCanOver(true);
  this->s = createRangeSlider(layout, eb::HSV::S_MIN, eb::HSV::S_MAX, "s: ");
  this->v = createRangeSlider(layout, eb::HSV::V_MIN, eb::HSV::V_MAX, "v: ");

  connect(this->h, &HsvFilterItemView::onChange, this, &HSVFilterView::handleSingleHSVChanged);
  connect(this->s, &HsvFilterItemView::onChange, this, &HSVFilterView::handleSingleHSVChanged);
  connect(this->v, &HsvFilterItemView::onChange, this, &HSVFilterView::handleSingleHSVChanged);
}

eb::HSVRange HSVFilterView::range() {
  return eb::HSVRange(
      eb::HSV(this->h->GetLowerValue(), this->s->GetLowerValue(), this->v->GetLowerValue()),
      eb::HSV(this->h->GetUpperValue(), this->s->GetUpperValue(), this->v->GetUpperValue()));
}

void HSVFilterView::handleSingleHSVChanged(int lower, int upper) {
  auto _range = range();
  if (this->hsvRange != _range) {
    this->hsvRange = _range;
    emit hsvRangeChange(range());
  }
}

HsvFilterItemView *HSVFilterView::createRangeSlider(QLayout *layout, int min, int max, const std::string &title) {
//  auto container = new QWidget();
//  auto cLayout = new QHBoxLayout(container);
//  auto label = new QLabel(title);
//  label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
//  cLayout->addWidget(label);
//
//  auto rst = new RangeSlider();
//  rst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//  rst->SetRange(min, max);
//  cLayout->addWidget(rst);
  auto rst = new HsvFilterItemView(title, min, max);

  layout->addWidget(rst);
  return rst;
}
