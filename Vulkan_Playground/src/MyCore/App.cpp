// app.cpp
#include "app.h"
#include <cassert>
#include "MyExp/FreeExcept.h"

app::app(HINSTANCE xHInstance)
	:
	myWindow(xHInstance)
{}

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

	VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	const char* debugVkLayers[] ={
		"VK_LAYER_KHRONOS_validation",
	};
	createInfo.pApplicationInfo = &appInfo;
	createInfo.ppEnabledLayerNames = debugVkLayers;
	createInfo.enabledLayerCount = sizeof(debugVkLayers) / sizeof(debugVkLayers[0]);

	const char* extensions[] =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
		//(If you're making a multiplatfom renderer, then you can define what platforms need)
	#ifdef _Win32 
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		std::cout << "64bit version";
	#endif
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
	};
	createInfo.ppEnabledExtensionNames = extensions;
	createInfo.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);


	// Create VkInstance
	VkInstance instance = nullptr;
	//the 0 in this function is for where we can pass in a custom memory allocator!
	VkResult result = vkCreateInstance(&createInfo, 0, &instance);
	assert(result == VK_SUCCESS);


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