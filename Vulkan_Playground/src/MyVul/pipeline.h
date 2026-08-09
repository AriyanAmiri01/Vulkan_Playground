#pragma once
#include "MyHeaders.h"
#include "MyVul/shader_loader.h"


class MyPipeline {
public:
	MyPipeline(VkDevice xDevice, VkExtent2D xExtent, VkRenderPass xRenderPass);
	~MyPipeline();
public:
	VkPipeline graphicsPipeline{};
	VkDevice vkDevice;
	VkShaderModule vertexShaderModule{};
	VkShaderModule fragmentShaderModule{};
	VkPipelineLayout pipelineLayout{};
};