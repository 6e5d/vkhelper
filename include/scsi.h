#ifndef _VKBASIC_SCSIH
#define _VKBASIC_SCSIH

#include <vulkan/vulkan.h>

void vkhelper_scsi(
	VkSurfaceFormatKHR* format,
	VkSurfaceCapabilitiesKHR* caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

#endif
