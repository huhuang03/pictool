//
// Created by huhua on 2021/11/7.
//

#ifndef PICTOOL_CENTRAL_IMAGE_H
#define PICTOOL_CENTRAL_IMAGE_H

#include <QLabel>

class CentralImage: public QLabel {
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *ev) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    double scale;
    bool isDragging;
    QPoint dragStartPoint;

public:
    CentralImage(QWidget *parent = nullptr);
};


#endif //PICTOOL_CENTRAL_IMAGE_H
