// WindowManager.cpp
#include "windowManager.h"


//////////////////////////////////////////////////////////////////////////////////
/// GETTERS FOR THE WINDOWSTATE STUFF
WPARAM windowManager::GetWindowState() const noexcept
{
	return windowState;
}
RECT windowManager::getWindowRect() const
{
	return windowRect;
}
int windowManager::GetTop() const noexcept
{
	return windowRect.top;
}
int windowManager::GetBottom() const noexcept
{
	return windowRect.bottom;
}
int windowManager::GetRight() const noexcept
{
	return windowRect.right;
}
int windowManager::GetLeft() const noexcept
{
	return windowRect.left;
}
int windowManager::GetWindowHeight() const noexcept
{
	return windowRect.bottom - windowRect.top;
}
int windowManager::GetWindowWidth() const noexcept
{
	return windowRect.right - windowRect.left;
}


//////////////////////////////////////////////////////////////////////////////////
/// GETTERS FOR THE WINDOWSTATE STUFF
int windowManager::GetWindowX() const noexcept
{
	return x;
}
int windowManager::GetWindowY() const noexcept
{
	return y;
}
void windowManager::changeWindowState(const WPARAM xWindowState)
{
	windowState = xWindowState;
	windowRect.left = 100;
	windowRect.top = 100;
}
void windowManager::changeWindowRect(RECT xRect)
{
	windowRect = xRect;
}
void windowManager::changeWindowWidth(const UINT xWidth)
{
	windowRect.right = windowRect.left + xWidth;
}
void windowManager::changeWindowHeight(const UINT xHeight)
{
	windowRect.bottom = windowRect.top + xHeight;

}
void windowManager::changeWindowX(const int short xX)
{
	x = LONG(xX);

}
void windowManager::changeWindowY(const int short xY)
{
	y = LONG(xY);
}