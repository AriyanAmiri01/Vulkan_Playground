#pragma once
// app.h
#include "MyWin/window.h"


class app
{
public:
	app(HINSTANCE xHInstance);
	void go();
	void doFrame();
private:
	MSG msg = {};
	window myWindow;
};