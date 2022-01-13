//
// Created by hwf on 2022/1/12.
//

#ifndef PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_
#define PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

/**
 * 图片住的View
 * How the paint do?
 */
class GraphicImageView: public QGraphicsView {
 private:
  QGraphicsPixmapItem *item;
  void updateImage();
  double _scale;
  QRect *_selectRect;
  QGraphicsRectItem *_selectItem;


 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;



 public:
  explicit GraphicImageView(QWidget *parent = nullptr);
  void setPixmap(const QPixmap &pixmap);
};

#endif //PICTOOL_SRC_UI_PANEL_MAIN_GRAPHIC_IMAGE_VIEW_H_
