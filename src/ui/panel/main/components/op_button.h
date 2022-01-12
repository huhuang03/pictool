//
// Created by hwf on 2022/1/12.
//

#ifndef PICTOOL_SRC_UI_PANEL_MAIN_COMPONENTS_OP_BUTTON_H_
#define PICTOOL_SRC_UI_PANEL_MAIN_COMPONENTS_OP_BUTTON_H_
#include <QString>

/**
 * 操作按钮
 */
class OpButton {
 private:
  QString imgPath;
  QString imgPathDisable;

 public:
  explicit OpButton(const QString &imgPath,
           const QString &imgPathDisable = QString(""));
};

#endif //PICTOOL_SRC_UI_PANEL_MAIN_COMPONENTS_OP_BUTTON_H_
