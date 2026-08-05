#pragma once
#include "MyHeaders.h"


class MyVkSurface {
public:
	MyVkSurface(HINSTANCE xInstance, HWND xHwnd, VkInstance xVkInstance, VkPhysicalDevice xPhysicalDevice);
	~MyVkSurface();

public:
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
	VkInstance vkInstance{};
	VkSurfaceCapabilitiesKHR caps{};
	VkSurfaceKHR surface{};
};