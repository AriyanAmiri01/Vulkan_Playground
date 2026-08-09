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

	// Read shaders
	auto vertexShaderCode = readFile("assets/shaders/vertex_shader.vert.spv");
	auto fragmentShaderCode = readFile("assets/shaders/frag_shader.frag.spv");

	// Create Pixel shader
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.codeSize = vertexShaderCode.size();
	createInfo.pCode =reinterpret_cast<const uint32_t*>(vertexShaderCode.data());

	VkShaderModule vertexShaderModule{};
	VK_CHECK(vkCreateShaderModule(
		myVulkanDevices->vulkanDeviceHnd,
		&createInfo,
		nullptr,
		&vertexShaderModule));


	// Create Fragment
	VkShaderModule fragmentShaderModule{};
	createInfo.codeSize = fragmentShaderCode.size();
	createInfo.pCode =reinterpret_cast<const uint32_t*>(fragmentShaderCode.data());

	VK_CHECK(vkCreateShaderModule(
		myVulkanDevices->vulkanDeviceHnd,
		&createInfo,
		nullptr,
		&fragmentShaderModule));



	// Create Pipeline shader stage
	VkPipelineShaderStageCreateInfo vertStage{};
	vertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertStage.module = vertexShaderModule;
	vertStage.pName = "main";
	VkPipelineShaderStageCreateInfo fragStage{};

	fragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragStage.module =fragmentShaderModule;
	fragStage.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] =
	{
		vertStage,
		fragStage
	};


	// Create Input state
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType =VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr;


	// Create Input assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType =VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology =VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable =VK_FALSE;

	// Create viewport state
	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width =static_cast<float>(myVulkanDevices->myVkSurface->extent.width);
	viewport.height =static_cast<float>(myVulkanDevices->myVkSurface->extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = myVulkanDevices->myVkSurface->extent;

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType =VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	// Create Rasterizer state
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType =VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType =VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.rasterizationSamples =VK_SAMPLE_COUNT_1_BIT;
	multisampling.sampleShadingEnable =VK_FALSE;
	multisampling.minSampleShading = 1.0f;
	multisampling.pSampleMask = nullptr;
	multisampling.alphaToCoverageEnable =VK_FALSE;
	multisampling.alphaToOneEnable =VK_FALSE;

	// Color blend
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask =
		VK_COLOR_COMPONENT_R_BIT |
		VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT |
		VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType =VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	// Create Pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType =VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pSetLayouts = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;

	VkPipelineLayout pipelineLayout{};
	VK_CHECK(vkCreatePipelineLayout(
		myVulkanDevices->vulkanDeviceHnd,
		&pipelineLayoutInfo,
		nullptr,
		&pipelineLayout));

	// Create Pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType =VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

	// Shader stages
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;

	// Fixed-function pipeline states
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr;

	// Pipeline layout
	pipelineInfo.layout = pipelineLayout;

	// Render pass compatibility
	pipelineInfo.renderPass = mySwapchain->renderPass;
	pipelineInfo.subpass = 0;

	// No pipeline derivation
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;

	VkPipeline graphicsPipeline{};

	VK_CHECK(vkCreateGraphicsPipelines(
		myVulkanDevices->vulkanDeviceHnd,
		VK_NULL_HANDLE,
		1,
		&pipelineInfo,
		nullptr,
		&graphicsPipeline));








	// destructors 
	vkDestroyShaderModule(myVulkanDevices->vulkanDeviceHnd, vertexShaderModule, nullptr);
	vkDestroyShaderModule(myVulkanDevices->vulkanDeviceHnd, fragmentShaderModule, nullptr);
	vkDestroyPipelineLayout(
		myVulkanDevices->vulkanDeviceHnd,
		pipelineLayout,
		nullptr);

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