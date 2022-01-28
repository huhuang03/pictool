//
// Created by huhua on 2021/8/20.
//

#ifndef PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
#define PIC_TOOL_CAPTURE_WINDOW_MANAGER_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>

// need single instance?
class CaptureWindowManager {
private:
    static CaptureWindowManager* _instance;

    POINT prePos{};

    bool hasStart = false;

public:
    static CaptureWindowManager *inst();
    void start();

    /**
     * This is a helper method for create thread,
     * in other words, you should not call this method
     */
    void _start();

private:

    /**
     * doCapture and set the flags.
     */
    void doCapture(const POINT &p);

    /**
     * Real do the capture, don't care the others.
     */
    void _doCaptureInner();
    void stop();
};
#endif


#endif //PIC_TOOL_CAPTURE_WINDOW_MANAGER_H
