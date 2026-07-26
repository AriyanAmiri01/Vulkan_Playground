#pragma once
// WindowManager.h
#include "MyHeaders.h"


class windowManager
{
public:
	WPARAM GetWindowState() const noexcept;
	RECT getWindowRect() const;
	int GetTop() const noexcept;
	int GetBottom() const noexcept;
	int GetRight() const noexcept;
	int GetLeft() const noexcept;
	int GetWindowHeight() const noexcept;
	int GetWindowWidth() const noexcept;
	int GetWindowX() const noexcept;
	int GetWindowY() const noexcept;
	void changeWindowWidth(const UINT xWidth);
	void changeWindowHeight(const UINT xHeight);
	void changeWindowX(const int short xX);
	void changeWindowY(const int short xY);
	void changeWindowState(const WPARAM xWindowState);
	void changeWindowRect(RECT xRect);
private:
	int x;
	int y;
	WPARAM windowState;
	RECT windowRect;
};