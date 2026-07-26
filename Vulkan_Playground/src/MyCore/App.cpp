// app.cpp
#include "app.h"


app::app(HINSTANCE xHInstance)
	:
	myWindow(xHInstance)
{}

void app::go()
{
	while (GetMessage(&msg, nullptr, 0, 0)) {
		// Getting the inputs
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Opdating the game logic

		// Rendering
		doFrame();
	}
}

void app::doFrame()
{}