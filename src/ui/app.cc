//
// Created by huhua on 2021/8/7.
//

#include "app.h"
#include "../module/size_config.h"
#include "../manager/capture/capture_window_manager.h"
#include <QtWidgets>
#include <pic_tool/settings/setting.h>

App* App::_inst = nullptr;
QtAwesome *App::awesome = nullptr;

App::App(): panelMain(new MainPanel) {
    settingInit(this);
    App::_inst = this;
    resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);

    setCentralWidget(this->panelMain);

    this->createActions();
    this->createDockers();
    this->createMenu();

    auto path = "C:/Users/huhua/Pictures/bb.bmp";
//    path = "C:/Users/hwf/Pictures/bb.bmp";
// 1920 x 1920
    path = "C:/Users/hwf/Pictures/bbb.jpeg";
//    if (!boost::file)
    // can I check the path exist.
    this->loadImage(path);

    this->panelMain->addImgAlter([this](cv::InputArray src, cv::OutputArray dst) {
        this->hsvFilterView->range().work(src, dst);
    });
}

void App::clickedCaptureWindow() {
    CaptureWindowManager::inst()->start();
}

void App::createActions() {
}

void App::createDockers() {
    auto dockHsvFilter = new QDockWidget(tr("hsv"), this);
    this->hsvFilterView = new HSVFilterView();
    dockHsvFilter->setWidget(hsvFilterView);
    addDockWidget(Qt::BottomDockWidgetArea, dockHsvFilter);
    connect(hsvFilterView, &HSVFilterView::hsvRangeChange, this, &App::onHsvRangeChanged);
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
            tr("Image Files(*.bmp)"));

    // I want save the previous select image, how to do it?
    if (imgFilePath.isNull()) {
        return;
    }

    settingSet(KEY_LAST_DIR, imgFilePath.toStdString());

    std::cout << "imgFilePath " << imgFilePath.toStdString() << std::endl;
    this->loadImage(imgFilePath.toStdString());
}

void App::loadImage(const std::string &path) {
    auto img = cv::imread(path);
    if (img.empty()) {
        qDebug() << "why img is empty";
        return;
    }
    panelMain->loadImage(img);
}

void App::onHsvRangeChanged(eb::HSVRange hsvRange) {
//    std::cout << "hsvRange: " << hsvRange << std::endl;
    this->panelMain->updateImg();
}

