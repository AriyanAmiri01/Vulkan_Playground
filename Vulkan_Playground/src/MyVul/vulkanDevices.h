#pragma once
#include "MyHeaders.h"
#include "MyVul/vulkanSurface.h"


class MyVulkanDevices {
public:
	MyVulkanDevices(VkInstance xVulkanInstance, HINSTANCE xInstance,HWND xHwnd, uint32_t xWndW, uint32_t xWndH);
	~MyVulkanDevices();
public:
	VkPhysicalDevice physicalDeviceHnd;	
	VkDevice vulkanDeviceHnd;
	std::shared_ptr<MyVkSurface> myVkSurface;
	uint32_t queueFamilyIndex;	// Index of selected queue in that phy device
	uint32_t deviceIndex; // Index of the Phy Graphic Device when you queury it
};