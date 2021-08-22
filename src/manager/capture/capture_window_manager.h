//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
#define PIC_TOOL_CAPTURE_WINDOW_MANAGER_H

#include <Windows.h>

// need single instance?
class CaptureWindowManager {
private:
    static CaptureWindowManager* _instance;

    POINT prePos;

public:
    static CaptureWindowManager *inst();
    void start();

private:
    void doCapture(const POINT &p);
    void stop();
};


#endif //PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
