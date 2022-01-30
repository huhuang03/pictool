//
// Created by th on 2022/1/30.
//

#include "hsv_filter_item_view.h"
#include "../../../../components/range-slider/RangeSlider.h"
#include <QHBoxLayout>


HsvFilterItemView::HsvFilterItemView(const std::string &title, int min, int max) {
  this->title = title;

  auto container = new QWidget();
  auto cLayout = new QHBoxLayout(container);
  this->label = new QLabel();
  this->label->setMinimumWidth(60);
  label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  cLayout->addWidget(label);

  this->rs = new RangeSlider();
  rs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  rs->SetRange(min, max);
  cLayout->addWidget(rs);

  this->setLayout(cLayout);
  this->updateLabel(min, max);

  this->connect(rs, &RangeSlider::valueChanged, this, &HsvFilterItemView::handleChange);
}

void HsvFilterItemView::updateLabel(int lower, int upper) {
  this->label->setText(QString("%1[%2-%3]")
                           .arg(title.c_str())
                           .arg(lower)
                           .arg(upper));
}

void HsvFilterItemView::handleChange(int lower, int upper) {
  this->updateLabel(lower, upper);
  emit onChange(lower, upper);
}

RangeSlider *HsvFilterItemView::getRangerSlider() {
  return this->rs;
}
