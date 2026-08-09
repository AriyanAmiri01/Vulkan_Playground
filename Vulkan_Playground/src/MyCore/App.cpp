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

	//std::cout << "Capability was:" << myVulkanDevices->myVkSurface->caps.currentTransform << std::endl;
	//myVulkanDevices->myVkSurface->TestSwapConfig();


	// Create the swapchain
	mySwapchain = std::make_shared<MySwapchain>(
		myVulkanDevices->vulkanDeviceHnd,
		myVulkanDevices->myVkSurface->surfaceFormat,
		myVulkanDevices->myVkSurface->presentMode,
		myVulkanDevices->myVkSurface->swapchainSupport.capabilities,
		myVulkanDevices->myVkSurface->extent,
		myVulkanDevices->myVkSurface->imageCount,
		myVulkanDevices->myVkSurface->surface
	);


	// Create Pipeline
	myPipeline = std::make_shared<MyPipeline>(
		myVulkanDevices->vulkanDeviceHnd,
		myVulkanDevices->myVkSurface->extent,
		mySwapchain->renderPass);

	// Create FrameBuffers
	std::vector<VkFramebuffer> framebuffers(mySwapchain->swapchainImages.size());
	for (size_t i = 0; i < framebuffers.size(); ++i)
	{
		VkImageView attachments[] =
		{
			mySwapchain->swapchainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType =VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.pNext = nullptr;
		framebufferInfo.flags = 0;

		// The render pass this framebuffer will be used with
		framebufferInfo.renderPass = mySwapchain->renderPass;

		// Our render pass has one attachment: the color attachment
		framebufferInfo.attachmentCount = 1;

		// Actual image view used for that attachment
		framebufferInfo.pAttachments = attachments;

		// Size of the framebuffer
		framebufferInfo.width = myVulkanDevices->myVkSurface->extent.width;
		framebufferInfo.height = myVulkanDevices->myVkSurface->extent.height;

		framebufferInfo.layers = 1;

		VkResult result = vkCreateFramebuffer(
			myVulkanDevices->vulkanDeviceHnd,
			&framebufferInfo,
			nullptr,
			&framebuffers[i]
		);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create framebuffer!");
		}
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