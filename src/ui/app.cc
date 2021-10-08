//
// Created by huhua on 2021/8/7.
//

#include "app.h"
#include "../size_config.h"
#include "../manager/capture/capture_window_manager.h"
#include <QtWidgets>
#include <QKeySequence>

App::App() {
    resize(SIZE_IMG_AREA_W, SIZE_IMG_AREA_H);
    this->createActions();
}

void App::clickedCaptureWindow() {
    CaptureWindowManager::inst()->start();
}

void App::createActions() {
    // The tool action
    auto menuTool = menuBar()->addMenu(tr("&Tool"));
    auto *captureWindowAct = new QAction("&Capture window");
    captureWindowAct->setShortcut(QKeySequence(tr("Ctrl+W")));
    connect(captureWindowAct, &QAction::triggered, this, &App::clickedCaptureWindow);
    menuTool->addAction(captureWindowAct);
}
