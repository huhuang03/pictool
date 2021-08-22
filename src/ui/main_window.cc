//
// Created by huhua on 2021/8/7.
//

#include "main_window.h"
#include "../size_config.h"
#include "../manager/capture/capture_window_manager.h"
#include <QtWidgets>

MainWindow::MainWindow() {
    resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);
    this->createActions();
}

void MainWindow::clickedCaptureWindow() {
    CaptureWindowManager::inst()->start();
}

void MainWindow::createActions() {
    // The tool action
    auto menuTool = menuBar()->addMenu(tr("&Tool"));
    auto *captureWindowAct = new QAction("Capture window");
    connect(captureWindowAct, &QAction::triggered, this, &MainWindow::clickedCaptureWindow);
    menuTool->addAction(captureWindowAct);
}
