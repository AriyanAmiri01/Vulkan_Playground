#pragma once
// windowCreator.h
#include "MyHeaders.h"
#include "windowClass.h"

class window;
class windowCreator
{
public:
	windowCreator(HINSTANCE xHInstance, window* xMyWindow);
	HWND getWindowHandler() const;
private:
	HWND hwnd;
};