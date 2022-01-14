//
// Created by hwf on 2022/1/14.
//

#ifndef PICTOOL_SRC_UI_PANEL_MAIN_OP_MODE_H_
#define PICTOOL_SRC_UI_PANEL_MAIN_OP_MODE_H_
enum OpMode {
  /**
   * 普通状态
   */
  NORMAL,

  /**
   * 截取部分
   */
  POI,

  /**
   * 拖动
   */
  MOVE,
};
#endif //PICTOOL_SRC_UI_PANEL_MAIN_OP_MODE_H_
