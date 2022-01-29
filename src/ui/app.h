//
// Created by huhua on 2021/8/7.
//

#ifndef PIC_TOOL_MAIN_WINDOW_H
#define PIC_TOOL_MAIN_WINDOW_H
#include <QWidget>
#include <QMainWindow>
#include "./panel/main/main_panel.h"
#include <QtAwesome.h>

#include <opencv2/opencv.hpp>
#include <easybot/model/hsv_range.h>
#include "panel/hsv/hsv_filter_view.h"
#include "panel/recently/recently_panel.h"

// I think you can find the QApplication your self.
class App: public QMainWindow {
    Q_OBJECT
public:
    App();
    static App* inst();
    // yes, if you are a static in App, then you are an external
    static QtAwesome *awesome;

private slots:
    void clickedCaptureWindow();
    void open();
    void onHsvRangeChanged(eb::HSVRange hsvRange);

private:
    static App* _inst;
    void createDockers();
    void createActions();
    void createMenu();
    MainPanel *panelMain;
    HSVFilterView *hsvFilterView;
    RecentlyPanel *panelRecent;
    cv::Mat img;

private:
    void loadImage(const std::string &path);
};


#endif //PIC_TOOL_MAIN_WINDOW_H
