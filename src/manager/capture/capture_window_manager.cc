//
// Created by huhua on 2021/8/20.
//

#include "capture_window_manager.h"
#include <Windows.h>
#include <iostream>
#include "../../util/util_eq.h"
#include "../../util/util.h"

const int CAPTURE_THRESHOLD = 1 * 1000;

void CaptureWindowManager::start() {
    POINT preP;
    unsigned long prePosTime = 0;

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }

        POINT  p;
        GetCursorPos(&p);

        if (eq(preP, p) && (ms() - prePosTime) > CAPTURE_THRESHOLD) {
            doCapture();
            break;
        } else {
            preP = p;
            prePosTime = ms();
        }


        Sleep(100);
    }
}

void CaptureWindowManager::doCapture() {
    std::cout << "do capture" << std::endl;
}
