//
// Created by huhua on 2022/1/22.
//

#ifndef PICTOOL_SRC_UI_PANEL_RECENTLY_RECENTLY_PANEL_H_
#define PICTOOL_SRC_UI_PANEL_RECENTLY_RECENTLY_PANEL_H_

#include <QWidget>
#include <vector>
#include <QListWidget>

class RecentlyPanel: public QWidget {
  Q_OBJECT
 public:
  RecentlyPanel(QWidget *parent = nullptr);

  signals:
  void onChoice(std::string);

 private:
  std::vector<std::string> paths;
  std::string chosen;
  void handleChoice(QListWidgetItem *item);
  void updateUI();
  QListWidget *listWidget;
  void save();
  void restore();


 public:
  void add(const std::string& path);
};

#endif //PICTOOL_SRC_UI_PANEL_RECENTLY_RECENTLY_PANEL_H_
