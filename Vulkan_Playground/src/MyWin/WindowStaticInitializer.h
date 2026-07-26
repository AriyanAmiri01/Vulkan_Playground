#pragma once
// WindowStaticInitializer.h
#include "MyHeaders.h"


class windowStaticInitializer
{
public:
	static LRESULT CALLBACK WndStaticProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};