#include "vulkanInstance.h"



VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,		// seriousness of the message (err, war, info, ect)
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,				// Type of the message
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,	// Actual message data
	void* pUserData												// Optional Pointer for farther communication
) {

	// Extract severty
	const char* severity = "UNKNOWN";
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
		severity = "ERROR";
	} else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		severity = "WARNING";
	} else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
		severity = "INFO";
	} else if (messageSeverity &
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
		severity = "VERBOSE";
	}

	// Extract Type
	const char* type = "UNKNOWN";
	if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
		type = "VALIDATION";
	} else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
		type = "PERFORMANCE";
	} else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
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


MyVulkanInstance::MyVulkanInstance()
{
	// Debug Callback
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	FillDebugMessengerCreateInfo(debugCreateInfo);

	const char* debugVkLayers[] = {
		"VK_LAYER_KHRONOS_validation",
	};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = &debugCreateInfo;
	createInfo.pApplicationInfo = &myVulkanApp.appInfo;
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

	//the 0 in this function is for where we can pass in a custom memory allocator!
	VkResult result;
	result = vkCreateInstance(&createInfo, 0, &vulkanInstance);
	VK_CHECK(result);

	
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
}

MyVulkanInstance::~MyVulkanInstance()
{
	if (debugMessenger != VK_NULL_HANDLE)
	{
		DestroyDebugMessenger(vulkanInstance, debugMessenger, nullptr);
	}
	if (vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(vulkanInstance, nullptr);
	}
}
