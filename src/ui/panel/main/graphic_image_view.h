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
  void onMove(QPoint pos, cv::Vec3b color);
  void onHistoryChange();

 private:
  cv::Mat _img;
  std::vector<QRectF> _history;
  int index = -1;
  std::stack<QRectF> _bckStack;
  std::stack<QRectF> _curStack;

  QGraphicsPixmapItem *item;
  void updateImageBySelect(QRectF selectRect);
  double _scale;
  QRect *_selectRect;
  QGraphicsRectItem *_roiItem;
  // not useful, actually.
  QPointF _selectStartPos;
  QPointF _selectStopPos;
  OpMode mode;

  /**
   * 是否在选择中
   */
  bool _isSelecting;

  inline bool isSelecting() {
    return _isSelecting;
  };

  /**
   * deprecated don't use this any more
   * @param pixmap
   */
  void setPixmap(const QPixmap &pixmap);

  void handleHistoryChanged();


 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 public:
  explicit GraphicImageView(QWidget *parent = nullptr);

  void setQImage(const QImage &img);
  void setImage(const cv::Mat &mat);

  inline void setMode(OpMode _mode) {
    this->mode = _mode;
  }

  inline bool canForward() {
    return this->index < this->_history.size() - 1;
  }

  inline bool canBackward() {
    return this->index > 0;
  }

  void move(const std::stack<QRectF> &from, std::stack<QRectF> &to);

 public slots:
  void forward();
  void backward();
};

#endif //PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_
