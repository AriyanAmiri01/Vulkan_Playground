// Window.cpp
#include "window.h"
#include "MyExp/FreeExcept.h"

////////////////////////////////////////////////////
/// WINDOW STUFFS
window::window(HINSTANCE xHInstance)
{
	windowCreator myWindowCreator(xHInstance, this);
	hwnd = myWindowCreator.getWindowHandler();
}
window::~window()
{
    if (hwnd != nullptr)
    {
        DestroyWindow(hwnd);
    }
}
HWND window::getHwnd() const
{
	return hwnd;
}