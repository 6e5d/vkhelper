#ifndef _VKBASIC_SCSIH
#define _VKBASIC_SCSIH

#include <vulkan/vulkan.h>

// swapchain support info
typedef struct {
	VkSurfaceFormatKHR format;
	VkSurfaceCapabilitiesKHR caps;
} VkhelperScsi;

VkhelperScsi vkhelper_scsi(
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

#endif
