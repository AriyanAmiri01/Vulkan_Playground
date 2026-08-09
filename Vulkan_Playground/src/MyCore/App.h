#pragma once
// app.h
#include "MyWin/window.h"
#include <memory>

#include "MyVul/shader_loader.h"

#include "MyVul/vulkanInstance.h"
#include "MyVul/vulkanDevices.h"
#include "MyVul/swapchain.h"


class app
{
public:
	app(HINSTANCE xHInstance);
	~app();
	void go();
	void doFrame();
private:
	window myWindow;
	MSG msg = {};
public:
	MyVulkanInstance myVulkanInstance;
	std::shared_ptr<MyVulkanDevices> myVulkanDevices;
	std::shared_ptr<MySwapchain> mySwapchain;
	
};