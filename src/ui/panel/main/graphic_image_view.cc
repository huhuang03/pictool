//
// Created by hwf on 2022/1/12.
//

#include "graphic_image_view.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <QScrollBar>

// pixmap's size:  QSize(618, 330) , thisSize:  QSize(800, 600)
// click at:  QMouseEvent(MouseButtonPress, LeftButton, localPos=751,289, screenPos=1323,537)
// click at:  QMouseEvent(MouseButtonPress, LeftButton, localPos=754,292, screenPos=1326,540)
// ok the loc pos is the GraphicImageView's current loc.
GraphicImageView::GraphicImageView(QWidget *parent)
: QGraphicsView(parent), _scale(1.0) {
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  auto *graphicScene = new QGraphicsScene();
  this->setScene(graphicScene);
  this->item = new QGraphicsPixmapItem();
  graphicScene->addItem(this->item);
}

void GraphicImageView::setPixmap(const QPixmap &pixmap) {
  this->item->setPixmap(pixmap);
  updateImage();
}

void GraphicImageView::updateImage() {
  auto pixmap = this->item->pixmap();

  auto thisSize = this->size();
  qDebug() << " pixmap's size: " << pixmap.size() << ", thisSize: " << thisSize;
  this->_scale = std::max(
      thisSize.width() * 1.0 / pixmap.size().width(),
      thisSize.height() * 1.0 / pixmap.size().height());

  qDebug() << "_scale: " << this->_scale;

  // for test.
//  scale = scale * 1.5;
//  scale = 1;
  this->scale(_scale, _scale);
}
void GraphicImageView::mouseDoubleClickEvent(QMouseEvent *event) {
  QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicImageView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  qDebug() << "click at: " << event;
  // ok, let's try calc the real pos
  auto xScroll = this->horizontalScrollBar()->value();
  auto yScroll = this->verticalScrollBar()->value();
  auto tmpX = xScroll + event->x();
  auto tmpY = yScroll + event->y();
  qDebug() << "real pos(before scale): " << tmpX << ", " << tmpY;
  qDebug() << "real pos: " << tmpX / this->_scale << ", " << tmpY / this->_scale;
}

void GraphicImageView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
}
void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);
}
