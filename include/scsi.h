#ifndef INCLUDEGUARD_VKHELPER_SCSIH
#define INCLUDEGUARD_VKHELPER_SCSIH

#include <vulkan/vulkan.h>

void vkhelper_scsi(
	VkSurfaceFormatKHR *format,
	VkSurfaceCapabilitiesKHR *caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

#endif
