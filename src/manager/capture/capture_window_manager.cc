//
// Created by huhua on 2021/8/20.
//

#include "capture_window_manager.h"
#include <Windows.h>
#include <iostream>
#include "../../util/util_eq.h"
#include "../../util/util.h"

const int CAPTURE_THRESHOLD = 1 * 1000;

const std::string AppFrameWindowClass = "ApplicationFrameWindow";

CaptureWindowManager* CaptureWindowManager::_instance = nullptr;

void CaptureWindowManager::start() {
    // ?? how to do this? 1??
    auto window = FindWindow(AppFrameWindowClass.c_str(), nullptr);
    std::cout << "start called, mainWindow: " << window << std::endl;
//    POINT preP;
//    unsigned long prePosTime = 0;
//
//    while (true) {
//        if (GetAsyncKeyState(VK_ESCAPE)) {
//            this->stop();
//            break;
//        }
//
//        POINT  p;
//        GetCursorPos(&p);
//
//        if (eq(preP, p) && (ms() - prePosTime) > CAPTURE_THRESHOLD) {
//            doCapture(p);
//            break;
//        } else {
//            preP = p;
//            prePosTime = ms();
//        }
//
//        Sleep(100);
//    }
}


static BOOL CALLBACK enumFindWindow(HWND hwnd, LPARAM param) {
    char title[1024];
    GetWindowText(hwnd, (LPSTR)&title, 1023);
    std::cout << "window name: " << title << std::endl;
    return true;
}

void CaptureWindowManager::doCapture(const POINT &p) {
    if (eq(this->prePos, p)) {
        return;
    }

    this->prePos.x = p.x;
    this->prePos.y = p.y;
    std::cout << "do capture" << std::endl;

    EnumWindows(enumFindWindow, 0);
}

void CaptureWindowManager::stop() {
    this->prePos.x = -1;
    this->prePos.y = -1;
}

CaptureWindowManager *CaptureWindowManager::inst() {
    if (_instance == nullptr) {
        _instance = new CaptureWindowManager();
    }
    return _instance;
}
