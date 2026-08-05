#include "vulkanApp.h"



MyVulkanApp::MyVulkanApp()
{
	// Prepare for Vulkan Instance Creation
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = "My Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "My Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
}
