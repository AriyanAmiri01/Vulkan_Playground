#include "vulkanDevices.h"

MyVulkanDevices::MyVulkanDevices(VkInstance xVulkanInstance)
{

	// Create Physical Device
	VkPhysicalDevice physicalDevices[16];
	uint32_t physicalDeviceCount = 16;
	uint32_t selectedDevice = -1;

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
	if (selectedDevice != -1) {
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

	// Create QueueFamilies Structure
	VkQueueFamilyProperties queues[16];
	uint32_t queuesCount = ARRAYSIZE(queues);
	uint32_t selectedQueue = 0;

	// Query Queue Familites
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[selectedDevice], &queuesCount, queues);

	// Select right queue
	for (uint32_t i = 0; i < queuesCount; i++)
	{
		//check if this queue is a graphics queue
		if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			selectedQueue = i;
			break;
			//return i;
		} else {
			printf("No Graphics Queues found, is this a Compute only device?");
			//return VK_QUEUE_FAMILY_IGNORED;
		}
	}

	// Store it 
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
}

MyVulkanDevices::~MyVulkanDevices()
{
	if (vulkanDeviceHnd != VK_NULL_HANDLE) {
		vkDestroyDevice(vulkanDeviceHnd, 0);
	}
}
