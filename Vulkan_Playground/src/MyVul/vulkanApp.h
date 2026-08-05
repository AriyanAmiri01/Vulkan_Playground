#pragma once
#include <MyHeaders.h>



class MyVulkanApp {
public:
	MyVulkanApp();
	// Prepare for Vulkan Instance Creation
public:
	VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
};