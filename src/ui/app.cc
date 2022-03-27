//
// Created by huhua on 2021/8/7.
//

#include "app.h"
#include <pictool/internal/capture_window_manager.h>
#include <QtWidgets>
#include <pictool/settings/setting.h>
#include <vector>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include "./panel/recently/recently_panel.h"
#include <pictool/internal/util.h>
#include <QFileDialog>

App *App::_inst = nullptr;
QtAwesome *App::awesome = nullptr;

static std::string getDefaultImgPath() {
  std::vector<std::string> pathes{"C:/Users/huhua/Pictures/11.bmp", "C:/Users/hwf/Pictures/111.jpg"};
  for (auto path : pathes) {
    if (boost::filesystem::exists(path)) {
      return path;
    }
  }
  return "";
}

App::App() : panelMain(new MainPanel) {
  settingInit(this);
  App::_inst = this;
  this->panelRecent = new RecentlyPanel();
  setCentralWidget(this->panelMain);

  this->createActions();
  this->createDockers();
  this->createMenu();

  auto path = getDefaultImgPath();

  this->loadImage(path);
}

void App::clickedCaptureWindow() {
//    CaptureWindowManager::inst()->start();
}

void App::createActions() {
}

void App::createDockers() {
  auto dockHsvFilter = new QDockWidget(tr("hsv"), this);
  this->hsvFilterView = new HSVFilterView();
  dockHsvFilter->setWidget(hsvFilterView);
  addDockWidget(Qt::BottomDockWidgetArea, dockHsvFilter);
  connect(hsvFilterView, &HSVFilterView::hsvRangeChange, this, &App::onHsvRangeChanged);

  auto dockerRecently = new QDockWidget(tr("recently"), this);
  dockerRecently->setWidget(this->panelRecent);
  addDockWidget(Qt::RightDockWidgetArea, dockerRecently);
  connect(this->panelRecent, &RecentlyPanel::onChoice, this, &App::loadImage);
}

void App::createMenu() {
  auto menuFile = menuBar()->addMenu(tr("&File"));
  auto openAction = new QAction(tr("&Open"));
  connect(openAction, &QAction::triggered, this, &App::open);
  menuFile->addAction(openAction);

  // The tool action
  auto menuTool = menuBar()->addMenu(tr("&Tool"));
  auto *captureWindowAct = new QAction("&Capture window");
  captureWindowAct->setShortcut(QKeySequence(tr("Ctrl+W")));
  connect(captureWindowAct, &QAction::triggered, this, &App::clickedCaptureWindow);
  menuTool->addAction(captureWindowAct);

  auto *crop = new QAction("&Crop");
  connect(crop, &QAction::triggered, this, &App::crop);
  menuTool->addAction(crop);

  auto *find = new QAction("&Find");
  connect(find, &QAction::triggered, this, &App::find);
  menuTool->addAction(find);
}

App *App::inst() {
  return App::_inst;
}

void App::open() {
  const std::string KEY_LAST_DIR = "last_dir";
  const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
  auto defaultDir = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
  auto dir = settingGet(KEY_LAST_DIR, defaultDir.toStdString());

  auto imgFilePath = QFileDialog::getOpenFileName(
      this,
      tr("Open an image file"),
      QString::fromUtf8(dir.c_str()),
      // for only we only bmp image.
      tr("Image Files(*.bmp, *.jpg, *.png)"));

  // I want save the previous select image, how to do it?
  if (imgFilePath.isNull()) {
    return;
  }

  settingSet(KEY_LAST_DIR, imgFilePath.toStdString());

  std::cout << "imgFilePath " << imgFilePath.toStdString() << std::endl;
  this->loadImage(imgFilePath.toStdString());
  this->panelRecent->add(imgFilePath.toStdString());
}

void App::loadImage(const std::string &path) {
  // did you real convert it?
  auto _img = cv::imread(path);

  // I want remove alpha
  if (_img.empty()) {
    return;
  }
  // this not work?
  this->img = _img;
  panelMain->loadImage(img, true);
}

void App::onHsvRangeChanged(eb::HSVRange hsvRange) {
  cv::Mat out;
  hsvRange.work(this->img, out);
  // how can I debug you?
//  cv::imshow("out", out);
  panelMain->loadImage(out, false);
}

void App::crop() {
  auto region = panelMain->getCropRegion();
  qDebug() << "region: " << region;
  // for now, prompt a file to write.
  cv::Mat roi(this->img,
              cv::Range(region.top(), region.bottom()),
              cv::Range(region.left(), region.right()));
  cv::imwrite("C:/Users/huhua/Desktop/11.bmp", roi);
}

void App::find() {
  // so you sayed that it's so easy and you can't do this?

//  cv::matchTemplate()
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), nullptr, tr("Image Files (*.png *.jpg *.bmp)"));
  if (fileName.isEmpty()) {
    return;
  }
  auto temp = cv::imread(fileName.toStdString());

  std::vector<int> methods = {cv::TM_CCOEFF, cv::TM_CCOEFF_NORMED,
                              cv::TM_CCORR, cv::TM_CCORR_NORMED,
                              cv::TM_SQDIFF, cv::TM_SQDIFF_NORMED
                              };
  std::vector<std::string> methodNames = {"TM_CCOEFF", "TM_CCOEFF_NORMED",
                                         "TM_CCORR", "TM_CCORR_NORMED",
                                         "TM_SQDIFF", "TM_SQDIFF_NORMED"};
  auto i = 0;
  for (const auto &method : methods) {
    auto methodName = methodNames[i++];
    cv::Mat copy;
    this->img.copyTo(copy);
    cv::Mat rst;
    cv::matchTemplate(copy, temp, rst, method);
    double min, max;
    cv::Point2i minLoc, maxLoc;
    cv::Point topLeft;
    cv::minMaxLoc(rst, &min, &max, &minLoc, &maxLoc);
    if (method == cv::TM_SQDIFF || method == cv::TM_SQDIFF_NORMED) {
      topLeft = minLoc;
    } else {
      topLeft = maxLoc;
    }
    cv::Point bottomRight = topLeft + cv::Point(temp.cols, temp.rows);
    cv::rectangle(copy, topLeft, bottomRight, 255, 2);
    cv::imshow("template " + methodName, rst);
    cv::imshow("origin " + methodName, copy);
  }
}
