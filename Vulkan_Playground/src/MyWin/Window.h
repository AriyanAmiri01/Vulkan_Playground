#pragma once
// Window.h
#include "windowCreator.h"
#include "MyKeyboard.h"
#include "MyMouse.h"
#include <memory>

class window
{
public:
	window(HINSTANCE xHInstance);
	HWND getHwnd() const;
	
	windowProcedure myWindowProcedure;
	windowManager myWindowManager{};
	MyKeyboard myKeyboard;
	MyMouse myMouse;
private:
	HWND hwnd;
};