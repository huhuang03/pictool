//
// Created by huhua on 2021/11/7.
//

#ifndef PICTOOL_CENTRAL_IMAGE_H
#define PICTOOL_CENTRAL_IMAGE_H

#include <QLabel>

/**
 * Let's first impl the roi.
 */
class CenterImageView: public QLabel {
    Q_OBJECT
 public:
  enum Mode {
    roi,
    move,
  };
protected:
  // so the key is what pos is you?
    void mouseMoveEvent(QMouseEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *ev) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    double scale;
    bool isDragging;
    QPoint dragStartPoint;
    Mode mode;

public:
  QPointF roiStart;
  explicit CenterImageView(QWidget *parent = nullptr);
};


#endif //PICTOOL_CENTRAL_IMAGE_H
