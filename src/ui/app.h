//
// Created by huhua on 2021/8/7.
//

#ifndef PIC_TOOL_MAIN_WINDOW_H
#define PIC_TOOL_MAIN_WINDOW_H
#include <QWidget>
#include <QMainWindow>

#include <opencv2/opencv.hpp>

// I think you can find the QApplication your self.
class App: public QMainWindow {
    Q_OBJECT
private:
    static App* _inst;

    // yes, img is the origin img;
    cv::Mat img;

public:
    App();
    static App* inst();

private:
    void createDockers();
    void createActions();
    void createMenu();

private slots:
    void clickedCaptureWindow();
    void open();
};


#endif //PIC_TOOL_MAIN_WINDOW_H
