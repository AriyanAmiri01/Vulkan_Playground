// Window.cpp
#include "window.h"

////////////////////////////////////////////////////
/// WINDOW STUFFS
window::window(HINSTANCE xHInstance)
{
	windowCreator myWindowCreator(xHInstance, this);
	hwnd = myWindowCreator.getWindowHandler();
}
HWND window::getHwnd() const
{
	return hwnd;
}