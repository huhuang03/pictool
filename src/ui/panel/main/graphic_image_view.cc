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
  setAlignment(Qt::AlignLeft | Qt::AlignTop);

  auto *group = new QGraphicsItemGroup;

  auto *graphicScene = new QGraphicsScene();
  this->setScene(graphicScene);
  this->item = new QGraphicsPixmapItem();
  group->addToGroup(this->item);

  this->_selectItem = new QGraphicsRectItem();
  this->_selectRect = new QRect(0, 0, 700, 700);
  this->_selectItem->setRect(*this->_selectRect);
  group->addToGroup(this->_selectItem);

  graphicScene->addItem(group);
}

void GraphicImageView::setPixmap(const QPixmap &pixmap) {
  this->item->setPixmap(pixmap);
  this->updateImageBySelect(QRectF(QPointF(0, 0), pixmap.size()));
}

void GraphicImageView::mouseDoubleClickEvent(QMouseEvent *event) {
  QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicImageView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
//  qDebug() << "click at: " << event;
  this->_selectStartPos = this->posToOrigin(event->pos());

  _selectRect->setRect((int)std::floor(this->_selectStartPos.x()),
                       (int)std::floor(this->_selectStartPos.y()), 0, 0);
  _selectRect->setRect(0, 0, 100, 100);
  _selectItem->setRect(*this->_selectRect);
//  qDebug() << "down rect: " << *_selectRect;
}

void GraphicImageView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  this->_selectStopPos = posToOrigin(event->pos());
//  qDebug() << "move rect: " << *_selectRect;
  _selectRect->setRight((int)std::ceil(this->_selectStopPos.x()));
  _selectRect->setBottom((int)std::ceil(this->_selectStopPos.y()));
  _selectItem->setRect(*this->_selectRect);
}

void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);


  QRectF rect(*this->_selectRect);
  this->updateImageBySelect(rect);
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

void GraphicImageView::updateImageBySelect(QRectF selectRect) {
  auto pixmap = this->item->pixmap();
// scale 之后的size是多少？
  auto dstSize = this->size();
  qDebug() << " dst size: " << dstSize << ", selectSize: " << selectRect;
//  qDebug() << "graphicScene size: " << this->item
  this->_scale = std::min(
      dstSize.width()  / selectRect.width(),
      dstSize.height() / selectRect.height());

  qDebug() << "_scale: " << this->_scale;

  this->translate(selectRect.x(), selectRect.y());
  // why scale cause initial (0, 0) change?
  this->scale(_scale, _scale);
}

