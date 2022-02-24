//
// Created by huhua on 2022/1/22.
//

#include "recently_panel.h"
#include <iostream>
#include <pictool/settings/setting.h>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

const static std::string KEY_RECENTLY = "key_recently";

RecentlyPanel::RecentlyPanel(QWidget *parent) {
  // hwo to do this
  this->listWidget = new QListWidget(this);
  this->restore();
  this->updateUI();
  connect(this->listWidget, &QListWidget::itemClicked, this, &RecentlyPanel::handleChoice);
}

// how to do the ui?
// fk, how to do this?
void RecentlyPanel::updateUI() {
  this->listWidget->clear();
  for (const auto &item: this->paths) {
    boost::filesystem::path p(item);
    // any better idea?
    this->listWidget->addItem(QString(p.filename().string().c_str()));
  }
}

void RecentlyPanel::save() {
  settingSet(KEY_RECENTLY, boost::algorithm::join(this->paths, ","));
}

void RecentlyPanel::restore() {
  const auto str = settingGet(KEY_RECENTLY, "");
  if (!str.empty()) {
    // hwo to do this?
    this->paths.clear();
    boost::split(this->paths, str, boost::is_any_of(","), boost::token_compress_on);
  }
}

void RecentlyPanel::add(const std::string& path) {
  if (path.empty()) {
    return;
  }

  if (std::find(this->paths.begin(), this->paths.end(), path) == this->paths.end()) {
    this->paths.insert(this->paths.begin(), path);
    this->save();
    this->updateUI();
  }
}

void RecentlyPanel::handleChoice(QListWidgetItem *item) {
  auto index = item->listWidget()->currentIndex().row();
//  std::cout << "index: " << index << std::endl;

  if (index >= this->paths.size()) {
    std::cerr << "why index > paths.size" << std::endl;
    return;
  }

  this->chosen = this->paths[index];
  emit onChoice(this->chosen);
}