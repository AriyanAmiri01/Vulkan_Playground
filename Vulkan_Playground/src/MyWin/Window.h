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
	~window();
	HWND getHwnd() const;
	
	windowProcedure myWindowProcedure;
	windowManager myWindowManager{};
	MyKeyboard myKeyboard;
	MyMouse myMouse;
	HINSTANCE hinstance;
	HWND hwnd;
private:
};