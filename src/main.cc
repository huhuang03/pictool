//
// Created by huhua on 2021/7/28.
//

#include <QApplication>
#include "./ui/app.h"

int main(int argc, char* argv[]) {
    QApplication q(argc, argv);
    App app;
    app.show();
    return QApplication::exec();
}