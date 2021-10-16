//
// Created by huhua on 2021/8/7.
//

#ifndef PIC_TOOL_MAIN_WINDOW_H
#define PIC_TOOL_MAIN_WINDOW_H
#include <QWidget>
#include <QMainWindow>
#include "./components/central_view/central_view.h"

#include <opencv2/opencv.hpp>

// I think you can find the QApplication your self.
class App: public QMainWindow {
    Q_OBJECT
public:
    App();
    static App* inst();

private slots:
    void clickedCaptureWindow();
    void open();

private:
    static App* _inst;

    void createDockers();
    void createActions();
    void createMenu();
    CentralView *centralView;

    // helper method
private:
    void loadImage(const std::string &path);
};


#endif //PIC_TOOL_MAIN_WINDOW_H
