#pragma once
// entryPoint.cpp
#include "MyCore/app.h"
#include "MyWin/myConsole.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    try {
        // We run the program
        myConsole console1;
        console1.go();
        app myApp(hInstance);
        myApp.go();
    } catch (freeExcept& e) {
        // Exception that don't have any origin
        MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
        return -1;
    } catch (...) {
        // Any type of exception
        MessageBoxA(nullptr, "An unknown exception has occurred", "Any Exception", MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }
    return 0;
}