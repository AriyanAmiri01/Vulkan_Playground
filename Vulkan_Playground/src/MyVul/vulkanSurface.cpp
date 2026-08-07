#include "vulkanSurface.h"
#include <algorithm>


SwapchainSupportDetails ArQuerySwapchainSupport(
	VkPhysicalDevice physicalDevice,
	VkSurfaceKHR surface
)
{
	/* @description 
		* It queries three properties of the swapchain support and return a 
		structure containing that data
			- Supported Capabilites of the surface {VkSurfaceCapabilitiesKHR}
			- Supported Formats {std::vector<VkSurfaceFormatKHR> formats}
			- Supported Presentation mode {std::vector<VkPresentModeKHR> presentModes}
	*/

	// The structure to be returned
	SwapchainSupportDetails details{};

	// 1. Query surface capabilities
	VK_CHECK(
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
			physicalDevice,
			surface,
			&details.capabilities
		)
	);

	// 2. Query supported surface formats
	uint32_t formatCount = 0;

	VK_CHECK(
		vkGetPhysicalDeviceSurfaceFormatsKHR(
			physicalDevice,
			surface,
			&formatCount,
			nullptr
		)
	);

	if (formatCount > 0)
	{
		details.formats.resize(formatCount);

		VK_CHECK(
			vkGetPhysicalDeviceSurfaceFormatsKHR(
				physicalDevice,
				surface,
				&formatCount,
				details.formats.data()
			)
		);

		details.formats.resize(formatCount);
	}

	// 3. Query supported presentation modes
	uint32_t presentModeCount = 0;

	VK_CHECK(
		vkGetPhysicalDeviceSurfacePresentModesKHR(
			physicalDevice,
			surface,
			&presentModeCount,
			nullptr
		)
	);

	if (presentModeCount > 0)
	{
		details.presentModes.resize(presentModeCount);

		VK_CHECK(
			vkGetPhysicalDeviceSurfacePresentModesKHR(
				physicalDevice,
				surface,
				&presentModeCount,
				details.presentModes.data()
			)
		);

		details.presentModes.resize(presentModeCount);
	}

	return details;
}







VkPresentModeKHR ArChooseSwapPresentMode(
	const std::vector<VkPresentModeKHR>& presentModes
)
{
	for (const auto& mode : presentModes)
	{
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return mode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}



VkExtent2D ArChooseSwapExtent(
	const VkSurfaceCapabilitiesKHR& capabilities,
	uint32_t windowWidth,
	uint32_t windowHeight
)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
	{
		return capabilities.currentExtent;
	}

	VkExtent2D extent{};

	extent.width = std::clamp(
		windowWidth,
		capabilities.minImageExtent.width,
		capabilities.maxImageExtent.width
	);

	extent.height = std::clamp(
		windowHeight,
		capabilities.minImageExtent.height,
		capabilities.maxImageExtent.height
	);

	return extent;
}



uint32_t ArChooseSwapImageCount(
	const SwapchainSupportDetails& xSwapchainSupport
) {
	uint32_t imageCount = 2;
	if (imageCount < xSwapchainSupport.capabilities.minImageCount)
	{
		EXCEPT_FREE("Two swapchain images are not enough");
	}
	if (xSwapchainSupport.capabilities.maxImageCount > 0 &&
		imageCount > xSwapchainSupport.capabilities.maxImageCount)
	{
		EXCEPT_FREE("Two swapchain images exceed the supported maximum");
	}
	return imageCount;
}



VkSurfaceFormatKHR ArChooseSurfaceFormat(
	const std::vector<VkSurfaceFormatKHR>& xSurfaceFormats
) 
{
	// Error Check
	if (xSurfaceFormats.empty())
	{
		EXCEPT_FREE("No supported surface formats");
	}

	// Select surface format
	VkSurfaceFormatKHR surfaceFormat = xSurfaceFormats[0];

	for (const auto& f : xSurfaceFormats)
	{
		if (f.format == VK_FORMAT_B8G8R8A8_SRGB &&
			f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return f;
		}
	}

	return surfaceFormat;
}


MyVkSurface::MyVkSurface(
	HINSTANCE xInstance,
	HWND xHwnd,
	VkInstance xVkInstance,
	VkPhysicalDevice xPhysicalDevice,
	uint32_t xWndW,
	uint32_t xWndH
)
	:vkInstance(xVkInstance)
{
	// SurfaceCreateInfo
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = xInstance;
	surfaceCreateInfo.hwnd = xHwnd;

	// Create Surface
	VK_CHECK(vkCreateWin32SurfaceKHR(xVkInstance, &surfaceCreateInfo, 0, &surface));


	// Query Swapchain Support
	swapchainSupport =
		ArQuerySwapchainSupport(
			xPhysicalDevice,
			surface);

	// Select surface format
	surfaceFormat = 
		ArChooseSurfaceFormat(
			swapchainSupport.formats);
	

	// Select Presentation Mode 
	presentMode = 
		ArChooseSwapPresentMode(swapchainSupport.presentModes);


	// Select Image Count (exactly two image for easier learning)
	imageCount = 
		ArChooseSwapImageCount(swapchainSupport);


	// Select the Extent
	extent = 
		ArChooseSwapExtent(
			swapchainSupport.capabilities,
			xWndW,
			xWndH);

	// Test stuffs
	TestSwapConfig();
}





MyVkSurface::~MyVkSurface()
{
	if (surface != VK_NULL_HANDLE) {
		vkDestroySurfaceKHR(vkInstance, surface, 0);
	}
}

void MyVkSurface::TestSwapConfig()
{
	
	auto& sc = swapchainSupport.capabilities;
	std::cout << "Swapchain queried values: " << std::endl
		<< "minImageCount is: " << sc.minImageCount << std::endl
		<< "maxImageCount is: " << sc.maxImageCount << std::endl
		<< "currentExtent height is: " << sc.currentExtent.height << std::endl
		<< "currentExtent width is: " << sc.currentExtent.width << std::endl
		<< "minImageExtent heigth is: " << sc.minImageExtent.height << std::endl
		<< "minImageExtent width is: " << sc.minImageExtent.width << std::endl
		<< "maxImageExtent height is: " << sc.maxImageExtent.height << std::endl
		<< "maxImageExtent width is: " << sc.maxImageExtent.width << std::endl
		<< "maxImageArrayLayers is: " << sc.maxImageArrayLayers << std::endl
		<< "supportedTransforms is: " << sc.supportedTransforms << std::endl
		<< "currentTransform is: " << sc.currentTransform << std::endl
		<< "supportedCompositeAlpha is: " << sc.supportedCompositeAlpha << std::endl
		<< "supportedUsageFlags is: " << sc.supportedUsageFlags << std::endl;


	std::cout << "Supported swapchain formats are: " << std::endl;
	for (const auto& f : swapchainSupport.formats)
	{
		std::cout
			<< "Format:{"
			<< string_VkFormat(f.format)
			<< "}\t"
			<< "Color space:{"
			<< string_VkColorSpaceKHR(f.colorSpace)
			<< "}"
			<< std::endl;
	}
		

	std::cout << "supported swapchain present modes are: " << std::endl;
	for (const auto& m : swapchainSupport.presentModes) {
		std::cout
			<< "Present Mode: "
			<< string_VkPresentModeKHR(m)
			<< std::endl;
	}

	std::cout<< "Selected surface format: " 
		<< "Format:{"
		<< string_VkFormat(surfaceFormat.format)
		<< "}\t"
		<< "Color space:{"
		<< string_VkColorSpaceKHR(surfaceFormat.colorSpace)
		<< "}"
		<< std::endl;

	std::cout 
		<< "Selected Present Mode:"
		<< string_VkPresentModeKHR(presentMode)
		<< std::endl;
	
	std::cout 
		<< "Selected ImageCount:"
		<< imageCount
		<< std::endl;

	std::cout << " Selected extent" 
		<< "Width:{" << extent.width 
		<< "}\t" 
		<< "Height{" << extent.height
		<< "}" 
		<< std::endl;
	
}
