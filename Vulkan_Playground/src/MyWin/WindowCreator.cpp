// windowCreator.cpp
#include "windowCreator.h"


windowCreator::windowCreator(HINSTANCE xHInstance, window* xMyWindow)
{
	windowClass wndClass(xHInstance);

	RECT wr;
	wr.left = 100;
	wr.right = 800 + wr.left;
	wr.top = 100;
	wr.bottom = 600 + wr.top;
	if(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw std::runtime_error("error in window rectangle");
	}

	hwnd = CreateWindow(
		wndClass.getClassName().c_str(),
		"Hello this is the window",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		xHInstance,
		xMyWindow
	);

	
	if(hwnd == NULL)
	{
		EXCEPT_FREE("Something");
		return ;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

}
HWND windowCreator::getWindowHandler() const
{
	return hwnd;
}