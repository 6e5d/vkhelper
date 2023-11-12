#ifndef INCLUDEGUARD_VKBASIC_SCSIH
#define INCLUDEGUARD_VKBASIC_SCSIH

#include <vulkan/vulkan.h>

void vkhelper_scsi(
	VkSurfaceFormatKHR* format,
	VkSurfaceCapabilitiesKHR* caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

#endif
