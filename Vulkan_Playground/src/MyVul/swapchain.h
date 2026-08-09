#pragma once
#include "MyHeaders.h"
#include <vector>



class MySwapchain {
public:
	MySwapchain(
		VkDevice xVkDevice,
		VkSurfaceFormatKHR xSurfaceFormat,
		VkPresentModeKHR xPresentMode,
		VkSurfaceCapabilitiesKHR xCap,
		VkExtent2D extent,
		uint32_t xImageCount,
		VkSurfaceKHR xSurface);
	~MySwapchain();
public:
	VkDevice vkDeviceHnd;
	VkRenderPass renderPass = VK_NULL_HANDLE;
	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;
};