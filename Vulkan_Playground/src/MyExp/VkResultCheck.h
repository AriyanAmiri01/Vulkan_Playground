#pragma once
#include "FreeExcept.h"
#include "vulkan/vulkan.h"
#include <iostream>




void HandleVkResult(VkResult xResult);

#define VK_CHECK(x) HandleVkResult(x);