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

static int CROP_THRESHOLD = 10;

// pixmap's size:  QSize(618, 330) , thisSize:  QSize(800, 600)
// click at:  QMouseEvent(MouseButtonPress, LeftButton, localPos=751,289, screenPos=1323,537)
// click at:  QMouseEvent(MouseButtonPress, LeftButton, localPos=754,292, screenPos=1326,540)
// ok the loc pos is the GraphicImageView's current loc.
//
/**
 * 首先我们
 * monthEvent中的坐标：为什么坐标呢。
 *
 * Links: https://stackoverflow.com/questions/14610568/how-to-use-the-qgraphicsviews-translate-function
 * @param parent
 */
GraphicImageView::GraphicImageView(QWidget *parent)
: QGraphicsView(parent), _scale(1.0), mode(OpMode::POI), _isSelecting(false) {
  setMouseTracking(true);
//  this->setTransformationAnchor(QGraphicsView::NoAnchor);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);

  auto *group = new QGraphicsItemGroup;

  auto *graphicScene = new QGraphicsScene();
  this->setScene(graphicScene);
  this->item = new QGraphicsPixmapItem();
  group->addToGroup(this->item);

  this->_selectItem = new QGraphicsRectItem();
  this->_selectRect = new QRect(0, 0, 0, 0);
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

// so what's the event pos?
void GraphicImageView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  if (mode == OpMode::POI) {
    this->_isSelecting = true;
  } else {
    return;
  }
  this->_selectStartPos = this->mapToScene(event->pos());

  _selectRect->setRect((int)std::floor(this->_selectStartPos.x()),
                       (int)std::floor(this->_selectStartPos.y()), 0, 0);
  _selectItem->setRect(*this->_selectRect);
}

void GraphicImageView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  emit onMove(this->mapToScene(event->pos()).toPoint(), cv::Scalar_<uint8_t>(255, 0, 0));

  if (!isSelecting()) {
    return;
  }
  this->_selectStopPos = this->mapToScene(event->pos());
  _selectRect->setRight((int)std::ceil(this->_selectStopPos.x()));
  _selectRect->setBottom((int)std::ceil(this->_selectStopPos.y()));
  _selectItem->setRect(*this->_selectRect);
}

void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  if (!isSelecting()) {
    return;
  }
  this->_isSelecting = false;
  QRectF rect(*this->_selectRect);
  this->updateImageBySelect(rect);
  _selectRect->setRect(0, 0, 0, 0);
  _selectItem->setRect(*this->_selectRect);
}

///**
// * 虽然返回一个对象，实际是由传入函数传递指针进来。
// */
//QPointF GraphicImageView::posToOrigin(const QPoint &pos) {
//
//  auto xScroll = this->horizontalScrollBar()->value();
//  auto yScroll = this->verticalScrollBar()->value();
//
//  // we need the pos on scene
//  auto tmpX = xScroll + pos.x();
//  auto tmpY = yScroll + pos.y();
//
//  qDebug() << "x: " << tmpX / this->_scale << ", y: " << tmpY / this->_scale;
//  qDebug() << "mapToScene: " << mapToScene(pos);
//
//  return {tmpX / this->_scale, tmpY / this->_scale};
//}

/**
 * selectRect is rect on scene
 */
void GraphicImageView::updateImageBySelect(QRectF selectRect) {
  if (selectRect.width() < CROP_THRESHOLD || selectRect.height() < CROP_THRESHOLD) {
    return;
  }
// scale 之后的size是多少？
  auto dstSize = this->size();
  qDebug() << " dst size: " << dstSize << ", selectSize: " << selectRect;
//  qDebug() << "graphicScene size: " << this->item
  auto scale = std::min(
      dstSize.width()  / selectRect.width(),
      dstSize.height() / selectRect.height());
  this->_scale = scale;
//  this->_scale = scale / this->_scale;

  qDebug() << "_scale: " << this->_scale;

  auto transX = selectRect.x() * this->_scale;
  auto transY = selectRect.y() * this->_scale;
  qDebug() << "transX: " << transX << ", transY: " << transY;
  // trans 好像是没有作用啊
//  this->translate(transX, transY);
  // why scale cause initial (0, 0) change?
  // 主要是注意这里可以连续scale的。
  // why not work?
  // 为什么又不起作用了？
  this->horizontalScrollBar()->setValue((int)transX);
  this->verticalScrollBar()->setValue((int)transY);
  this->scale(_scale, _scale);
}

void GraphicImageView::forward() {
  auto rect = this->_selectPops.top();
  this->updateSceneRect(rect);
  this->_selects.push(rect);
  this->_selects.pop();
}

void GraphicImageView::backward() {

}

