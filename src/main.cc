//
// Created by huhua on 2021/7/28.
//

#include <QtWidgets>
#include "./ui/main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}