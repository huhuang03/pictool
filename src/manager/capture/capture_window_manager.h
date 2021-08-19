//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
#define PIC_TOOL_CAPTURE_WINDOW_MANAGER_H


// need single instance?
class CaptureWindowManager {
public:
    void start();

private:
    void doCapture();
};


#endif //PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
