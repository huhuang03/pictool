//
// Created by huhua on 2021/7/28.
//

#include <pic_tool/global.h>
#include <QApplication>
#include "./ui/app.h"

int main(int argc, char* argv[]) {
    QApplication q(argc, argv);
    gAwesome = new QtAwesome(&q);
    App app;
    app.show();
    return q.exec();
}