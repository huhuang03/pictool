//
// Created by hwf on 2022/1/12.
//

#ifndef PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_
#define PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QRectF>
#include "op_mode.h"

#include <opencv2/core.hpp>
#include <stack>

/**
 * 图片住的View
 * How the paint do?
 */
class GraphicImageView: public QGraphicsView {
  Q_OBJECT;
  signals:
  void onMove(QPoint pos, cv::Scalar_<uint8_t> color);

 private:
  std::stack<QRectF> _selects;
  std::stack<QRectF> _selectPops;

  QGraphicsPixmapItem *item;
  void updateImageBySelect(QRectF selectRect);
  double _scale;
  QRect *_selectRect;
  QGraphicsRectItem *_selectItem;
  // not useful, actually.
  QPointF _selectStartPos;
  QPointF _selectStopPos;
  OpMode mode;
  /**
   * 是否在选择中
   */
  bool _isSelecting;

//  /**
//   * 点击事件的位置，变化为GraphicScene上的坐标
//   * @return
//   */
//  QPointF posToOrigin(const QPoint& pos);

  inline bool isSelecting() {
    return _isSelecting;
  };


 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 public:
  explicit GraphicImageView(QWidget *parent = nullptr);
  void setPixmap(const QPixmap &pixmap);
  inline void setMode(OpMode _mode) {
    this->mode = _mode;
  }

  inline bool canForward() {
    return !_selectPops.empty();
  }

  inline bool canBackward() {
    return !_selects.empty();
  }

  void forward();
  void backward();
};

#endif //PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_
