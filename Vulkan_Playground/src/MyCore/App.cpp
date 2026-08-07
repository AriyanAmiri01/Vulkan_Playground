// app.cpp
#include "app.h"
#include <cassert>
#include "MyExp/FreeExcept.h"
#include "MyExp/VkResultCheck.h"




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


	
	// Create Vulkan Instance
	VkInstance vulkanInstance = myVulkanInstance.vulkanInstance;
	if (vulkanInstance == VK_NULL_HANDLE) {
		EXCEPT_FREE("Failed to get vulkan instance");
	}




	// Create Physical and logical device
	auto clientRect = myWindow.getClientRect();
	myVulkanDevices = 
		std::make_shared<MyVulkanDevices>(
			myVulkanInstance.vulkanInstance,
			myWindow.hinstance,
			myWindow.hwnd,
			clientRect.clientWidth,
			clientRect.clientHeight
		);




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