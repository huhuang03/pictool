//
// Created by huhua on 2021/8/20.
//

#include "pictool/internal/capture_window_manager.h"
#include <Windows.h>
#include <iostream>
#include "pictool/internal/util/util_eq.h"
#include "pictool/internal/util.h"

const int CAPTURE_THRESHOLD = 1 * 1000;

const std::string AppFrameWindowClass = "ApplicationFrameWindow";

CaptureWindowManager* CaptureWindowManager::_instance = nullptr;

static DWORD WINAPI staticStart(void *param) {
    auto* captureMgr = (CaptureWindowManager*)param;
    captureMgr->_start();
    return 0;
}

void CaptureWindowManager::start() {
    if (this->hasStart) {
        std::cout << "already started" << std::endl;
        return;
    }
    this->hasStart = true;
    CreateThread(nullptr, 0, staticStart, this, 0,nullptr);
    // ?? how to do this? 1??
    // we need a better algorithm. Do you think so?
//    auto window = FindWindow(AppFrameWindowClass.c_str(), nullptr);
//    std::cout << "start called, mainWindow: " << window << std::endl;
// strange that we need a new thread to capture this?
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

    this->_doCaptureInner();
}

void CaptureWindowManager::stop() {
    this->prePos.x = -1;
    this->prePos.y = -1;
    this->hasStart = false;
    std::cout << "stop called" << std::endl;
}

CaptureWindowManager *CaptureWindowManager::inst() {
    if (_instance == nullptr) {
        _instance = new CaptureWindowManager();
    }
    return _instance;
}

BOOL CALLBACK _doCaptureInnerEnumWindows(HWND hwnd, LPARAM param) {
    // do here is also ok.
    // It's better to show the window??
    auto *p = (POINT*)param;

    if (!IsWindowVisible(hwnd)) {
        return true;
    }

    if (IsIconic(hwnd)) {
        return true;
    }

    RECT rect;
    GetWindowRect(hwnd, &rect);

    // we need a better idea to find the front window.
    if (rect.left <= p->x & rect.right >= p->x && rect.top <= p->y && rect.bottom >= p->y) {
        auto len = GetWindowTextLength(hwnd);

        auto pszMem = (PSTR) VirtualAlloc((LPVOID) NULL,
                                     (DWORD) (len + 1), MEM_COMMIT,
                                     PAGE_READWRITE);
        GetWindowText(hwnd, pszMem,
                      len + 1);
        std::cout << "the window: " << pszMem <<  std::endl;
//        return false;
    }
    return true;


    // but how to check the window is visible?

    // but latter we need handle the z-index.

    // later we will try the eg::Window
}

void CaptureWindowManager::_doCaptureInner() {
    // 1. First find all the top window
    EnumWindows(_doCaptureInnerEnumWindows, (LPARAM)&this->prePos);
    // 2. Second get the current pos and find the right window
    // 3. show the windows.
}

void CaptureWindowManager::_start() {
    POINT preP;
    unsigned long prePosTime = 0;

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            this->stop();
            break;
        }

        POINT  p;
        GetCursorPos(&p);


        if (eq(preP, p) && (pt::ms() - prePosTime) > CAPTURE_THRESHOLD) {
            doCapture(p);
            break;
        }

        if (!eq(preP, p)) {
            preP = p;
            prePosTime = pt::ms();
        }

        Sleep(200);
    }
}
