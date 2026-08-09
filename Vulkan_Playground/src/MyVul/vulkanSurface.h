#pragma once
#include "MyHeaders.h"
#include <vector>



struct SwapchainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities{};
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

SwapchainSupportDetails ArQuerySwapchainSupport(
	VkPhysicalDevice physicalDevice,
	VkSurfaceKHR surface);




class MyVkSurface {
public:
	MyVkSurface(HINSTANCE xInstance, HWND xHwnd, VkInstance xVkInstance, VkPhysicalDevice xPhysicalDevice, uint32_t xWndW, uint32_t xWndH);
	~MyVkSurface();

public:
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
	VkInstance vkInstance{};
	VkSurfaceCapabilitiesKHR caps{};
	VkSurfaceKHR surface{};
public: // Swap chain configurations
	void TestSwapConfig();
	SwapchainSupportDetails swapchainSupport;
	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	uint32_t imageCount;
	VkExtent2D extent;
};