//
// Created by hwf on 2022/1/12.
//

#include "graphic_image_view.h"
#include <qdebug.h>
#include <QMouseEvent>
#include <QScrollBar>
#include "../../../comm/util/util_cv.h"
// why you not work? so strange.
#include <pt/util.h>

static int CROP_THRESHOLD = 10;

/**
 * Links: https://stackoverflow.com/questions/14610568/how-to-use-the-qgraphicsviews-translate-function
 * @param parent
 */
GraphicImageView::GraphicImageView(QWidget *parent)
: QGraphicsView(parent), _scale(1.0), mode(OpMode::ROI), _isSelecting(false) {
  setMouseTracking(true);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);

  auto *group = new QGraphicsItemGroup;

  auto *graphicScene = new QGraphicsScene();
  this->setScene(graphicScene);
  this->item = new QGraphicsPixmapItem();
  group->addToGroup(this->item);

  this->_roiItem = new QGraphicsRectItem();
  this->_selectRect = new QRect(0, 0, 0, 0);
  this->_roiItem->hide();
  this->_roiItem->setRect(*this->_selectRect);
  group->addToGroup(this->_roiItem);

  graphicScene->addItem(group);
}


void GraphicImageView::setQImage(const QImage &img) {
  QImage2Mat(img, this->_img);
  this->setPixmap(QPixmap::fromImage(img));
}

void GraphicImageView::setPixmap(const QPixmap &pixmap) {
  this->item->setPixmap(pixmap);
  pt::clear(this->_forwards);
  this->handleHistoryChanged();
}

void GraphicImageView::mouseDoubleClickEvent(QMouseEvent *event) {
  QGraphicsView::mouseDoubleClickEvent(event);
}

// so what's the event pos?
void GraphicImageView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  if (mode == OpMode::ROI) {
    this->_roiItem->show();
    this->_selectStartPos = this->mapToScene(event->pos());

    _selectRect->setRect((int)std::floor(this->_selectStartPos.x()),
                         (int)std::floor(this->_selectStartPos.y()), 0, 0);
    _roiItem->setRect(*this->_selectRect);
  }

}

void GraphicImageView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);
  auto pos = this->mapToScene(event->pos()).toPoint();
  cv::Scalar_<uint8_t> color{0, 0, 0};
  if (QPointInMat(this->_img, pos)) {
    color = this->_img.at<cv::Scalar_<uint8_t>>(pos.x(), pos.y());
  }
  emit onMove(pos, color);

  if (this->mode == OpMode::ROI) {
    this->_selectStopPos = this->mapToScene(event->pos());
    _selectRect->setRight((int)std::ceil(this->_selectStopPos.x()));
    _selectRect->setBottom((int)std::ceil(this->_selectStopPos.y()));
    _roiItem->setRect(*this->_selectRect);
  }
}

void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  this->_roiItem->hide();
  if (this->mode == OpMode::ROI) {
    this->_isSelecting = false;
    this->_forwards.push(*this->_selectRect);
    this->handleHistoryChanged();
  }
}

/**
 * @param selectRect size in scene.
 */
void GraphicImageView::updateImageBySelect(QRectF selectRect) {
  if (selectRect.width() < CROP_THRESHOLD || selectRect.height() < CROP_THRESHOLD) {
    return;
  }
// scale 之后的size是多少？
  auto dstSize = this->size();
  qDebug() << " dst size: " << dstSize << ", selectSize: " << selectRect;
  auto scale = std::min(
      dstSize.width()  / selectRect.width(),
      dstSize.height() / selectRect.height());
  qDebug() << "scale: " << scale;
  this->_scale = scale / this->_scale;

  // trans是起作用的，只是好像值不对啊。
  // 这个是scale之前还是之后的？
  this->scale(_scale, _scale);

  auto tryTrans = this->mapFromScene(selectRect.topLeft());
  auto transX = tryTrans.x();
  auto transY = tryTrans.y();
  this->horizontalScrollBar()->setValue((int)transX);
  this->verticalScrollBar()->setValue((int)transY);
}

void GraphicImageView::forward() {
  this->move(this->_backwards, this->_forwards);
}

void GraphicImageView::backward() {
  this->move(this->_forwards, this->_backwards);
}

void GraphicImageView::setImage(const cv::Mat &mat) {
    this->_img = mat;
    this->setQImage(QImage((unsigned char *) mat.data, mat.cols, mat.rows, QImage::Format_BGR888));
}

void GraphicImageView::move(const std::stack<QRectF> &from, std::stack<QRectF> &to) {
  if (!from.empty()) {
    auto rect = from.top();
    this->updateSceneRect(rect);
    to.push(rect);
    to.pop();
    this->handleHistoryChanged();
  }
}

void GraphicImageView::handleHistoryChanged() {
  emit onHistoryChange();
  if (this->_forwards.empty()) {
    auto size = this->_img.size();
    this->updateImageBySelect(QRectF(QPointF(0, 0), QSize(size.width, size.height)));
  } else {
    auto rect = this->_forwards.top();
    this->updateImageBySelect(rect);
  }
}
