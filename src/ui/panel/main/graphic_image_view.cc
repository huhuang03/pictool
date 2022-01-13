//
// Created by hwf on 2022/1/12.
//

#include "graphic_image_view.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <QScrollBar>
#include <QRect>

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

//  this->_selectItem = new QGraphicsRectItem();
//  this->_selectRect->setRect(0, 0, 100, 100);
//  QPen pen(Qt::black);
//  this->_selectRect = graphicScene->addRect(0, 0, 0, 0, pen);
//  this->_selectItem->setRect(this->_selectRect);
  // this seems not work?
  graphicScene->addItem(this->item);

  this->_selectItem = new QGraphicsRectItem();
  this->_selectRect = new QRect(0, 0, 100, 100);
  this->_selectItem->setRect(*this->_selectRect);
  graphicScene->addItem(this->_selectItem);
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
//  qDebug() << "click at: " << event;
  auto realPos = this->posToOrigin(event->pos());

  _selectRect->setRect((int)std::floor(realPos.x()), (int)std::floor(realPos.y()), 0, 0);
  _selectItem->setRect(*this->_selectRect);
//  qDebug() << "down rect: " << *_selectRect;
}

void GraphicImageView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  auto pos = posToOrigin(event->pos());
//  qDebug() << "move rect: " << *_selectRect;
  _selectRect->setRight((int)std::ceil(pos.x()));
  _selectRect->setBottom((int)std::ceil(pos.y()));
  _selectItem->setRect(*this->_selectRect);
}

void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  _selectRect->setRect(0, 0, 0, 0);
  _selectItem->setRect(*this->_selectRect);
}

/**
 * 虽然返回一个对象，实际是由传入函数传递指针进来。
 */
QPointF GraphicImageView::posToOrigin(const QPoint &pos) {
  auto xScroll = this->horizontalScrollBar()->value();
  auto yScroll = this->verticalScrollBar()->value();

  // we need the pos on scene
  auto tmpX = xScroll + pos.x();
  auto tmpY = yScroll + pos.y();
  return {tmpX / this->_scale, tmpY / this->_scale};
}
