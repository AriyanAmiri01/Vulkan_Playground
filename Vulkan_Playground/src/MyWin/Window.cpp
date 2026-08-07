// Window.cpp
#include "window.h"
#include "MyExp/FreeExcept.h"

////////////////////////////////////////////////////
/// WINDOW STUFFS
window::window(HINSTANCE xHInstance)
{
	windowCreator myWindowCreator(xHInstance, this);
	hwnd = myWindowCreator.getWindowHandler();
    hinstance = xHInstance;
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

clientRectSize window::getClientRect() const
{
    // Structure to be filled
    RECT clientRect{};
    if (!GetClientRect(hwnd, &clientRect))
    {
        EXCEPT_FREE("Failed to retrieve Win32 client area.");
    }

    // Query Client Rect
    LONG clientWidth = clientRect.right - clientRect.left;
    LONG clientHeight = clientRect.bottom - clientRect.top;
    if (clientWidth <= 0 || clientHeight <= 0)
    {
        EXCEPT_FREE("Invalid Win32 client area dimensions.");
    }

    // Return
    clientRectSize temp{};
    temp.clientHeight = clientHeight;
    temp.clientWidth = clientWidth;
    return temp;
}
