#pragma once
// app.h
#include "MyWin/window.h"


#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>


class app
{
public:
	app(HINSTANCE xHInstance);
	~app();
	void go();
	void doFrame();
private:
	window myWindow;
	MSG msg = {};
};