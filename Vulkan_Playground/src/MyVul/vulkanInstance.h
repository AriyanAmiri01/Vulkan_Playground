#pragma once
#include "MyHeaders.h"
#include "MyVul/vulkanApp.h"

class MyVulkanInstance {
public:
	MyVulkanInstance();
	~MyVulkanInstance();

public:
	MyVulkanApp myVulkanApp;
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	VkInstanceCreateInfo createInfo{};
	VkInstance vulkanInstance = VK_NULL_HANDLE;
 };