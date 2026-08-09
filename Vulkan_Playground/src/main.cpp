#pragma once
// entryPoint.cpp
#include "MyCore/app.h"
#include "MyWin/myConsole.h"
#include "MyExp/FreeExcept.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    try {
        // We run the program
        myConsole console1;
        console1.go();
        printf(" ---=== No body loves me! =( ===---\n");
        app myApp(hInstance);
        myApp.go();
    } catch (freeExcept& e) {
        MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
    } catch (...) {
        MessageBoxA(nullptr, "An unknown exception has occurred", "Any Exception", MB_OK | MB_ICONEXCLAMATION);
    }

     return 0;
}