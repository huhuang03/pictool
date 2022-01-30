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
  label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  cLayout->addWidget(label);

  auto rst = new RangeSlider();
  rst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  rst->SetRange(min, max);
  cLayout->addWidget(rst);

  this->setLayout(cLayout);
  this->updateLabel(min, max);

  this->connect(rst, &RangeSlider::valueChanged, this, &HsvFilterItemView::handleChange);
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
