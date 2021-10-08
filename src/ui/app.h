//
// Created by huhua on 2021/8/7.
//

#ifndef PIC_TOOL_MAIN_WINDOW_H
#define PIC_TOOL_MAIN_WINDOW_H
#include <QWidget>
#include <QMainWindow>


// I think you can find the QApplication your self.
class App: public QMainWindow {
    Q_OBJECT
public:
    App();

private:
    void createActions();

private slots:
    void clickedCaptureWindow();
};


#endif //PIC_TOOL_MAIN_WINDOW_H
