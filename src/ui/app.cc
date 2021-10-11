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

App* App::_inst = nullptr;

App::App() {
    App::_inst = this;
    resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);

    QWidget *central = new QWidget();
    setCentralWidget(central);

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
    auto imgFilePath = QFileDialog::getOpenFileName(
            this,
            tr("Open an image file"),
            "",
            tr("Image Files(*.png *.jpg *.bmp)"));
    std::cout << "imgFilePath: " << imgFilePath.data() << std::endl;
}
