#pragma once
#include "MyHeaders.h"



class MyVulkanDevices {
public:
	MyVulkanDevices(VkInstance xVulkanInstance);
	~MyVulkanDevices();
public:
	VkPhysicalDevice physicalDeviceHnd;	
	VkDevice vulkanDeviceHnd;
};