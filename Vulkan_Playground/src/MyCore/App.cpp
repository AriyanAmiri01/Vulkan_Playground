// app.cpp
#include "app.h"
#include <cassert>
#include "MyExp/FreeExcept.h"
#include "MyExp/VkResultCheck.h"



VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,		// seriousness of the message (err, war, info, ect)
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,				// Type of the message
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,	// Actual message data
	void* pUserData												// Optional Pointer for farther communication
) {

	// Extract severty
	const char* severity = "UNKNOWN";
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
		severity = "ERROR";
	} 
	else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT){
		severity = "WARNING";
	} 
	else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT){
		severity = "INFO";
	} 
	else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT){
		severity = "VERBOSE";
	}

	// Extract Type
	const char* type = "UNKNOWN";
	if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
		type = "VALIDATION";
	} 
	else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT){
		type = "PERFORMANCE";
	} 
	else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT){
		type = "GENERAL";
	}

	// Extract Message
	char message[4096];
	std::snprintf(
		message,
		sizeof(message),
		"[DEBUG_UTILS_EXT][%s][%s]\n"
		"Message ID: %s (%d)\n"
		"%s\n\n",
		severity,
		type,
		pCallbackData->pMessageIdName
		? pCallbackData->pMessageIdName
		: "Unknown",
		pCallbackData->messageIdNumber,
		pCallbackData->pMessage
		? pCallbackData->pMessage
		: "No message");

	std::fprintf(stderr, "%s", message);

#ifdef _WIN32
	OutputDebugStringA(message);
#endif

	/*
	Avoid asserting here initially.
	A validation error does not necessarily mean that Vulkan is in a state
	where aborting from inside the callback is safe or useful.
	*/

	return VK_FALSE;
}

void FillDebugMessengerCreateInfo(
	VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};

	createInfo.sType =
		VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	createInfo.messageSeverity =
		//VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |	[TODO] for farther debuging
		//VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | [TODO] for farther debuging
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	createInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createInfo.pfnUserCallback = VulkanDebugCallback;
	createInfo.pUserData = nullptr;
}
VkResult CreateDebugMessenger(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto createFunction =
		reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
			vkGetInstanceProcAddr(
				instance,
				"vkCreateDebugUtilsMessengerEXT"));

	if (createFunction == nullptr)
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	return createFunction(
		instance,
		pCreateInfo,
		pAllocator,
		pDebugMessenger);
}


void DestroyDebugMessenger(
	VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator)
{
	auto destroyFunction =
		reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
			vkGetInstanceProcAddr(
				instance,
				"vkDestroyDebugUtilsMessengerEXT"));

	if (destroyFunction != nullptr)
	{
		destroyFunction(
			instance,
			debugMessenger,
			pAllocator);
	}
}

app::app(HINSTANCE xHInstance)
	:
	myWindow(xHInstance)
{}

app::~app()
{
}

void app::go()
{
	/* @title App initializer */
	/* @description Initialiazes render engine and other stuffs from the game */

	// Prepare for Vulkan Instance Creation
	VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = "My Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "My Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	
	// Debug Callback
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	FillDebugMessengerCreateInfo(debugCreateInfo);

	VkInstanceCreateInfo createInfo{};
	const char* debugVkLayers[] ={
		"VK_LAYER_KHRONOS_validation",
	};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = &debugCreateInfo;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.ppEnabledLayerNames = debugVkLayers;
	createInfo.enabledLayerCount = sizeof(debugVkLayers) / sizeof(debugVkLayers[0]);
	const char* extensions[] =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
		//(If you're making a multiplatfom renderer, then you can define what platforms need)
	#ifdef _WIN32 
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	#endif
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
	};
	createInfo.ppEnabledExtensionNames = extensions;
	createInfo.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);


	// Create VkInstance
	VkInstance vulkanInstance = VK_NULL_HANDLE;
	//the 0 in this function is for where we can pass in a custom memory allocator!
	VkResult result;
	result =  vkCreateInstance(&createInfo, 0, &vulkanInstance);
	VK_CHECK(result);

	// Create Messenger 
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	result = CreateDebugMessenger(
		vulkanInstance,
		&debugCreateInfo,
		nullptr,
		&debugMessenger);

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error(
			"Failed to create Vulkan debug messenger.");
	}

	





	// Create Physical Device
	VkPhysicalDevice physicalDevices[16];
	uint32_t physicalDeviceCount = 16;
	uint32_t selectedDevice = -1;

	// Query Physical Devices
	vkEnumeratePhysicalDevices(vulkanInstance, &physicalDeviceCount, physicalDevices);
	
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
			printf("Found discrete GPU: %s\n", props.deviceName);
			selectedDevice = i;
			break;
			// return physicalDevice[i];
		}
	}
	if (selectedDevice != -1) {
		// Fix this in the function definition by returning instead of creating stupid if statement
	}else if (physicalDeviceCount > 0)
	{
		// Search for anything else
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(physicalDevices[0], &props);
		printf("No discrete GPU found, falling back to GPU: %s\n", props.deviceName);
		selectedDevice = 0;
		//return physicalDevices[0];
	} else {
		EXCEPT_FREE("NO GPU SUPPORTING VULKAN FOUND");
	}


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
		if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
			selectedQueue = i;
			break;
			//return i;
		} else {
			printf("No Graphics Queues found, is this a Compute only device?");
			//return VK_QUEUE_FAMILY_IGNORED;
		}
	}
	
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
	const char* extensions2[] =
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
	deviceCreateInfo.enabledExtensionCount = ARRAYSIZE(extensions2);
	deviceCreateInfo.ppEnabledExtensionNames = extensions2;
	deviceCreateInfo.pEnabledFeatures = NULL;

	VkDevice vulkanDevice;
	VK_CHECK(vkCreateDevice(physicalDevices[selectedDevice], &deviceCreateInfo, 0, &vulkanDevice));


	// Surface creation
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = myWindow.hinstance;
	surfaceCreateInfo.hwnd = myWindow.getHwnd();

	VkSurfaceKHR surface = 0;
	VK_CHECK(vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceCreateInfo, 0, &surface));

	// Query surface format
	uint32_t surfaceFormatCount = 8;
	VkSurfaceFormatKHR surfaceFormats[8];
	VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevices[selectedDevice], surface, &surfaceFormatCount, surfaceFormats));

	// Selecting the surface format
	for (uint32_t i = 0; i < surfaceFormatCount; i++) {
		//[DEBUG] : printf("Supported Format: %i with color space: %i \n", surfaceFormats[i].format, surfaceFormats[i].colorSpace); 
	}
	auto surfaceFormat = surfaceFormats[0];

	// Queury surface Capability
	VkSurfaceCapabilitiesKHR caps;
	VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevices[selectedDevice], surface, &caps));
	




	//Destructor stuffs
	if (surface != VK_NULL_HANDLE) {
		vkDestroySurfaceKHR(vulkanInstance, surface, 0);
	}

	if (debugMessenger != VK_NULL_HANDLE)
	{
		DestroyDebugMessenger(vulkanInstance,debugMessenger,nullptr);
	}
	if (vulkanDevice != VK_NULL_HANDLE) {
		vkDestroyDevice(vulkanDevice, 0);
	}
	if (vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(vulkanInstance, nullptr);
	}

	


	/* @title Main game loop */
	/* @description Containing of three main steps of input handling, gamelogic update and rendering*/
	bool isRunning = true;

	while (isRunning) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			// Quit messgae
			if (msg.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}

			// Message Proccess
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (!isRunning){
			break; 
		}
		
		
		doFrame();
	}
}

void app::doFrame()
{

}