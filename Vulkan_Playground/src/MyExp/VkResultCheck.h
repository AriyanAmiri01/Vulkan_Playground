#pragma once
#include "FreeExcept.h"
#include "vulkan/vulkan.h"
#include <iostream>




void HandleVkResult(VkResult xResult) {
    // Ignore it was seccussful
    if (xResult == VK_SUCCESS) {
        return;
    }

    // Get the Result messaage
    const char* message = "Unknown VkResult.";
    switch (xResult)
    {

        case VK_NOT_READY:
        message = "A fence or query has not yet completed.";
        break;

        case VK_TIMEOUT:
        message = "A wait operation has not completed in the specified time.";
        break;

        case VK_EVENT_SET:
        message = "An event is signaled.";
        break;

        case VK_EVENT_RESET:
        message = "An event is unsignaled.";
        break;

        case VK_INCOMPLETE:
        message = "A return array was too small for the result.";
        break;

        case VK_SUBOPTIMAL_KHR:
        message = "Swapchain is suboptimal.";
        break;

#ifdef VK_THREAD_IDLE_KHR
        case VK_THREAD_IDLE_KHR:
        message = "Deferred operation: no work for this thread.";
        break;
#endif

#ifdef VK_THREAD_DONE_KHR
        case VK_THREAD_DONE_KHR:
        message = "Deferred operation: this thread has finished.";
        break;
#endif

#ifdef VK_OPERATION_DEFERRED_KHR
        case VK_OPERATION_DEFERRED_KHR:
        message = "Operation was deferred.";
        break;
#endif

#ifdef VK_OPERATION_NOT_DEFERRED_KHR
        case VK_OPERATION_NOT_DEFERRED_KHR:
        message = "Operation was not deferred.";
        break;
#endif

#ifdef VK_PIPELINE_COMPILE_REQUIRED
        case VK_PIPELINE_COMPILE_REQUIRED:
        message = "Pipeline compilation is required.";
        break;
#endif

#ifdef VK_PIPELINE_BINARY_MISSING_KHR
        case VK_PIPELINE_BINARY_MISSING_KHR:
        message = "Pipeline binary missing.";
        break;
#endif

#ifdef VK_INCOMPATIBLE_SHADER_BINARY_EXT
        case VK_INCOMPATIBLE_SHADER_BINARY_EXT:
        message = "Shader binary is incompatible.";
        break;
#endif

    // Error codes
        case VK_ERROR_OUT_OF_HOST_MEMORY:
        message = "Host memory allocation failed.";
        break;

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        message = "Device memory allocation failed.";
        break;

        case VK_ERROR_INITIALIZATION_FAILED:
        message = "Initialization failed.";
        break;

        case VK_ERROR_DEVICE_LOST:
        message = "The Vulkan device was lost.";
        break;

        case VK_ERROR_MEMORY_MAP_FAILED:
        message = "Memory mapping failed.";
        break;

        case VK_ERROR_LAYER_NOT_PRESENT:
        message = "Requested validation layer not present.";
        break;

        case VK_ERROR_EXTENSION_NOT_PRESENT:
        message = "Requested extension not present.";
        break;

        case VK_ERROR_FEATURE_NOT_PRESENT:
        message = "Requested feature not supported.";
        break;

        case VK_ERROR_INCOMPATIBLE_DRIVER:
        message = "Incompatible Vulkan driver.";
        break;

        case VK_ERROR_TOO_MANY_OBJECTS:
        message = "Too many Vulkan objects created.";
        break;

        case VK_ERROR_FORMAT_NOT_SUPPORTED:
        message = "Format not supported.";
        break;

        case VK_ERROR_FRAGMENTED_POOL:
        message = "Memory pool fragmented.";
        break;

        case VK_ERROR_SURFACE_LOST_KHR:
        message = "Surface lost.";
        break;

        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        message = "Native window already in use.";
        break;

        case VK_ERROR_OUT_OF_DATE_KHR:
        message = "Swapchain out of date.";
        break;

        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        message = "Incompatible display.";
        break;

#ifdef VK_ERROR_INVALID_SHADER_NV
        case VK_ERROR_INVALID_SHADER_NV:
        message = "Shader compilation or linking failed.";
        break;
#endif

        case VK_ERROR_OUT_OF_POOL_MEMORY:
        message = "Pool memory allocation failed.";
        break;

        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        message = "Invalid external handle.";
        break;

        case VK_ERROR_FRAGMENTATION:
        message = "Descriptor pool fragmentation.";
        break;

#ifdef VK_ERROR_INVALID_DEVICE_ADDRESS_EXT
        case VK_ERROR_INVALID_DEVICE_ADDRESS_EXT:
        message = "Invalid device address.";
        break;
#endif

        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        message = "Invalid opaque capture address.";
        break;

#ifdef VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        message = "Exclusive fullscreen mode lost.";
        break;
#endif

#ifdef VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT
        case VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT:
        message = "Present timing queue is full.";
        break;
#endif

        case VK_ERROR_VALIDATION_FAILED_EXT:
        message = "Validation failed.";
        break;

#ifdef VK_ERROR_COMPRESSION_EXHAUSTED_EXT
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
        message = "Compression resources exhausted.";
        break;
#endif

#ifdef VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR
        case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
        message = "Image usage not supported.";
        break;
#endif

#ifdef VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR
        case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
        message = "Video picture layout not supported.";
        break;
#endif

#ifdef VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR
        case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
        message = "Video profile operation not supported.";
        break;
#endif

#ifdef VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR
        case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
        message = "Video profile format not supported.";
        break;
#endif

#ifdef VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR
        case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
        message = "Video codec not supported.";
        break;
#endif

#ifdef VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR
        case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
        message = "Video standard version not supported.";
        break;
#endif

#ifdef VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR
        case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
        message = "Invalid video standard parameters.";
        break;
#endif

#ifdef VK_ERROR_NOT_PERMITTED
        case VK_ERROR_NOT_PERMITTED:
        message = "Operation not permitted.";
        break;
#endif

#ifdef VK_ERROR_NOT_ENOUGH_SPACE_KHR
        case VK_ERROR_NOT_ENOUGH_SPACE_KHR:
        message = "Not enough space provided.";
        break;
#endif

        case VK_ERROR_UNKNOWN:
        message = "Unknown Vulkan error.";
        break;

        default:
        {
            static std::string unknown;
            unknown = "Unknown VkResult (" + std::to_string(xResult) + ").";
            message = unknown.c_str();
            break;
        }
    }

    // Handle VkResult
    if (xResult > VK_SUCCESS)
    {
        std::cout << "[Vulkan VkResult] " << message << '\n';
    } else
    {
        std::string temp = "VkResult Message:";
        temp.append(message);
        EXCEPT_FREE(temp);
    }
}

#define VK_CHECK(x) HandleVkResult(x);