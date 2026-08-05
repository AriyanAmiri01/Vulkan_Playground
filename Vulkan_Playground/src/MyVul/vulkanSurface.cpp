#include "vulkanSurface.h"

MyVkSurface::MyVkSurface(HINSTANCE xInstance, HWND xHwnd, VkInstance xVkInstance, VkPhysicalDevice xPhysicalDevice)
	:vkInstance(xVkInstance)
{


	// Surface creation
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = xInstance;
	surfaceCreateInfo.hwnd = xHwnd;


	VK_CHECK(vkCreateWin32SurfaceKHR(xVkInstance, &surfaceCreateInfo, 0, &surface));

	// Query surface format
	uint32_t surfaceFormatCount = 8;
	VkSurfaceFormatKHR surfaceFormats[8];
	VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(xPhysicalDevice, surface, &surfaceFormatCount, surfaceFormats));

	// Selecting the surface format
	for (uint32_t i = 0; i < surfaceFormatCount; i++) {
		//[DEBUG] : printf("Supported Format: %i with color space: %i \n", surfaceFormats[i].format, surfaceFormats[i].colorSpace); 
	}
	auto surfaceFormat = surfaceFormats[0];

	// Queury surface Capability
	VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(xPhysicalDevice, surface, &caps));






}

MyVkSurface::~MyVkSurface()
{
	if (surface != VK_NULL_HANDLE) {
		vkDestroySurfaceKHR(vkInstance, surface, 0);
	}
}
