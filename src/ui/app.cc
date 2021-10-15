//
// Created by huhua on 2021/8/7.
//

#include "app.h"
#include "../module/size_config.h"
#include "../manager/capture/capture_window_manager.h"
#include <QtWidgets>
#include <QDockWidget>
#include "../components/hsv_filter/hsv_filter_view.h"
#include <QKeySequence>
#include <QDebug>

App* App::_inst = nullptr;

App::App(): centralView(new CentralView) {
    App::_inst = this;
    resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);

    setCentralWidget(this->centralView);

//    auto path = "C:/Users/huhua/Pictures/407555e7-4df4-4e56-b57e-3a449f2d904d-thumbnail.jpg";
//    auto path = "C:\\Users\\huhua\\Pictures\\407555e7-4df4-4e56-b57e-3a449f2d904d-thumbnail.jpg";
//    auto img = cv::imread(path);
//    auto img = cv::imread("C:/Users/huhua/Pictures/407555e7-4df4-4e56-b57e-3a449f2d904d-thumbnail.jpg");

    this->createActions();
    this->createDockers();
    this->createMenu();
}

void App::clickedCaptureWindow() {
    CaptureWindowManager::inst()->start();
}

void App::createActions() {
}

void App::createDockers() {
    auto dockHsvFilter = new QDockWidget(tr("hsv"), this);
    dockHsvFilter->setWidget(new HSVFilterView());
    addDockWidget(Qt::BottomDockWidgetArea, dockHsvFilter);
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
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    auto dir = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();

    auto imgFilePath = QFileDialog::getOpenFileName(
            this,
            tr("Open an image file"),
            dir,
            tr("Image Files(*.png *.jpg *.bmp)"));
    if (imgFilePath.isNull()) {
        return;
    }

    qDebug() << "imgFilePath: " << imgFilePath;
    std::cout << "imgFilePath1 " << imgFilePath.toStdString() << std::endl;
    // maybe arrow at here.
    // 这里很奇怪，有些jpg图片会抛异常。
    auto img = cv::imread(imgFilePath.toStdString());
//    this->centralView->loadImage(img);
//    std::cout << "imgFilePath: " << imgFilePath.toUtf8() << std::endl;
}

