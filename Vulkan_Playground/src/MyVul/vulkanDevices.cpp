#include "vulkanDevices.h"


MyVulkanDevices::MyVulkanDevices(
	VkInstance xVulkanInstance,
	HINSTANCE xInstance,
	HWND xHwnd,
	uint32_t xWndW,	/* [TODO] After separating surface and swapchain settings,  remove this parameter since only swapchain configuration needs it */ 
	uint32_t xWndH
)
{

	// Create Physical Device
	VkPhysicalDevice physicalDevices[16];
	uint32_t physicalDeviceCount = 16;
	uint32_t selectedDevice = UINT32_MAX;

	// Query Physical Devices
	vkEnumeratePhysicalDevices(xVulkanInstance, &physicalDeviceCount, physicalDevices);

	// Select Physical Device
	for (uint32_t i = 0; i < physicalDeviceCount; ++i)
	{
		// Get information about the device, name, type, etc.
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(physicalDevices[i], &props);

		// Search for the correct one
		if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			// Search for a dedicated graphic device
			// [DEBUG]: printf("Found discrete GPU: %s\n", props.deviceName);
			selectedDevice = i;
			break;
			// return physicalDevice[i];
		}
	}
	if (selectedDevice != UINT32_MAX) {
		// Fix this in the function definition by returning instead of creating stupid if statement
	} else if (physicalDeviceCount > 0)
	{
		// Search for anything else
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(physicalDevices[0], &props);
		// [DEBUG]: printf("No discrete GPU found, falling back to GPU: %s\n", props.deviceName);
		selectedDevice = 0;
		//return physicalDevices[0];
	} else {
		EXCEPT_FREE("NO GPU SUPPORTING VULKAN FOUND");
	}

	// Store it
	physicalDeviceHnd = physicalDevices[selectedDevice];

	// Surface Creation
		// Create Vulkan Surface
	myVkSurface = std::make_shared<MyVkSurface>(
		xInstance,
		xHwnd,
		xVulkanInstance,
		physicalDeviceHnd,
		xWndW,
		xWndH);


	// Create QueueFamilies Structure
	VkQueueFamilyProperties queues[16];
	uint32_t queuesCount = ARRAYSIZE(queues);
	uint32_t selectedQueue = UINT32_MAX;

	// Query Queue Familites
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[selectedDevice], &queuesCount, queues);
	
	// Select right queue
	for (uint32_t i = 0; i < queuesCount; i++)
	{
		// Check presentation capability
		VkBool32 supportsPresentation = VK_FALSE;
		VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(
				physicalDeviceHnd,
				i,
				myVkSurface->surface,
				&supportsPresentation
			)
		);

		// Check for Graphic cability
		const bool supportsGraphics = (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0;
		
		if (supportsGraphics && supportsPresentation == VK_TRUE)
		{
			selectedQueue = i;
			break;
		}
	}
	if (selectedQueue == UINT32_MAX)
	{
		EXCEPT_FREE("No queue family supports both graphics and presentation.");
	}

	// Store it 
	deviceIndex = selectedDevice;
	queueFamilyIndex = selectedQueue;
	VkQueueFamilyProperties queueFamily = queues[selectedQueue];

	// Add Queue information
	float queuePriorties[] = { 1.0f };
	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = NULL;
	deviceQueueCreateInfo.flags = NULL;
	deviceQueueCreateInfo.queueFamilyIndex = selectedQueue;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = queuePriorties;

	// extensions to enable for this device
	const char* extensions[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = NULL;
	deviceCreateInfo.flags = NULL;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = NULL;
	deviceCreateInfo.enabledExtensionCount = ARRAYSIZE(extensions);
	deviceCreateInfo.ppEnabledExtensionNames = extensions;
	deviceCreateInfo.pEnabledFeatures = NULL;

	// Create Vulkan Device
	VK_CHECK(vkCreateDevice(physicalDevices[selectedDevice], &deviceCreateInfo, 0, &vulkanDeviceHnd));

	// Retriving queuers
	VkQueue graphicsQueueHnd = VK_NULL_HANDLE;
	VkQueue presentQueueHnd = VK_NULL_HANDLE;

	vkGetDeviceQueue(
		vulkanDeviceHnd,
		selectedQueue,
		0,
		&graphicsQueueHnd
	);
	if (graphicsQueueHnd == VK_NULL_HANDLE)
	{
		EXCEPT_FREE("Failed to retrieve graphics queue.");
	}
	presentQueueHnd = graphicsQueueHnd;	// I used the same queue for both presentation and graphics


}

MyVulkanDevices::~MyVulkanDevices()
{
	if (vulkanDeviceHnd != VK_NULL_HANDLE) {
		vkDestroyDevice(vulkanDeviceHnd, 0);
	}
}
