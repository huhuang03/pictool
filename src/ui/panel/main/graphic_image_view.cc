//
// Created by hwf on 2022/1/12.
//

#include "graphic_image_view.h"
#include <qdebug.h>
#include <QMouseEvent>
#include <QScrollBar>
#include "pictool/internal/util/util_cv.h"
#include <pictool/internal/util.h>
#include <cmath>
#include <QTransform>

static int CROP_THRESHOLD = 10;

/**
 * Links: https://stackoverflow.com/questions/14610568/how-to-use-the-qgraphicsviews-translate-function
 * @param parent
 */
GraphicImageView::GraphicImageView(QWidget *parent)
: QGraphicsView(parent), _scale(1.0), mode(OpMode::ROI), _isSelecting(false) {
  setMouseTracking(true);
  setTransformationAnchor(QGraphicsView::NoAnchor);
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
  this->_history.clear();
  this->_history.emplace_back(pixmap.rect());
  this->index = 0;
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
  auto posF = this->mapToScene(event->pos());
  auto pos = QPoint((int)posF.x(), (int)posF.y());

  cv::Vec3b color{0, 0, 0};
  if (QPointInMat(this->_img, pos)) {
    color = this->_img.at<cv::Vec3b>(pos.y(), pos.x());
  }

  emit onMove(pos, color);

  if (this->mode == OpMode::ROI) {
    this->_selectStopPos = posF;
    _selectRect->setRight(pos.x());
    _selectRect->setBottom(pos.y());

    _roiItem->setRect(*this->_selectRect);
  }
}

void GraphicImageView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  this->_roiItem->hide();

  if (this->mode == OpMode::ROI) {
    this->_isSelecting = false;

    if (this->canForward()) {
      this->_history.erase(this->_history.begin() + 1, this->_history.end());
    }

    this->_history.emplace_back(*this->_selectRect);
    this->index = this->_history.size() - 1;
    this->handleHistoryChanged();
  }
}

/**
 * @param selectRect size in scene.
 */
void GraphicImageView::updateImageBySelect(QRectF selectRect) {
  auto rect = selectRect.normalized();
  if (rect.width() < CROP_THRESHOLD || rect.height() < CROP_THRESHOLD) {
    return;
  }
  auto dstSize = this->size();
//  qDebug() << " dst size: " << dstSize << ", selectSize: " << rect;
  auto widthScale = dstSize.width()  / rect.width();
  auto heightScale = dstSize.height() / rect.height();


  auto scale = min(widthScale, heightScale);
  QTransform trans = QTransform().translate(-rect.x(), -rect.y())
      * QTransform().scale(scale, scale);
  this->setTransform(trans);
}

void GraphicImageView::forward() {
  if (this->canForward()) {
    this->index += 1;
    this->handleHistoryChanged();
  }
}

void GraphicImageView::backward() {
  if (this->canBackward()) {
    this->index -= 1;
    this->handleHistoryChanged();
  }
}

void GraphicImageView::setImage(const cv::Mat &mat) {
    this->_img = mat;
    this->setQImage(QImage((unsigned char *) mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888));
}

void GraphicImageView::move(const std::stack<QRectF> &from, std::stack<QRectF> &to) {
  if (!from.empty()) {
    auto rect = from.top();
    qDebug() << "pop: " << rect;
    this->updateSceneRect(rect);
    to.push(rect);
    to.pop();
    this->handleHistoryChanged();
  }
}

void GraphicImageView::handleHistoryChanged() {
  emit onHistoryChange();
  if (!this->_history.empty()) {
    auto rect = this->_history[this->index];
    this->updateImageBySelect(rect);
  }
}
