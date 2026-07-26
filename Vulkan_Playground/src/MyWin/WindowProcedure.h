#pragma once
// WindowProcedure.h
#include "MyHeaders.h"
#include "windowManager.h"


class window;
class windowProcedure
{
public:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, window* xMyWindow);
public:
    static void moveHandler(LPARAM xLParam, window* xMyWindow);
    static void handleChangeWindow(HWND xHwnd, LPARAM xLParam, window* xMyWindow);
    static void handleChar(WPARAM wParam, window* xMyWindow);
    static void handleSyskeyUp(WPARAM wParam, window* xMyWindow);
    static void handleSyskeyDown(WPARAM wParam, LPARAM lParam, window* xMyWindow);
    static void handleKeyDown(WPARAM wParam, LPARAM lParam, window* xMyWindow);
    static void handleKeyUp(WPARAM wParam, window* xMyWindow);
public:
    static void handleMouseMove(LPARAM xLParam, window* xMyWindow);
    static void handleRPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleRRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleLPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleLRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleMPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleMRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow);
    static void handleMouseScroll(WPARAM xWParam, window* xMyWindow);
    static void handleMouseEnter(window* xMyWindow);
    static void handleMouseExit(window* xMyWindow);
};