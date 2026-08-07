#pragma once
// Window.h
#include "windowCreator.h"
#include "MyKeyboard.h"
#include "MyMouse.h"
#include <memory>


struct clientRectSize {
	uint32_t clientWidth;
	uint32_t clientHeight;
};

class window
{
public:
	window(HINSTANCE xHInstance);
	~window();
	HWND getHwnd() const;
	clientRectSize getClientRect() const;
public:
	windowProcedure myWindowProcedure;
	windowManager myWindowManager{};
	MyKeyboard myKeyboard;
	MyMouse myMouse;
	HINSTANCE hinstance;
	HWND hwnd;
private:
};