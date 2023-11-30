#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

void vkhelper_scsi(
	VkSurfaceFormatKHR *format,
	VkSurfaceCapabilitiesKHR *caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
) {
	assert(0 == vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		pdev, surface, caps));
	uint32_t count;
	assert(0 == vkGetPhysicalDeviceSurfaceFormatsKHR(
		pdev, surface, &count, NULL));
	VkSurfaceFormatKHR *formats = malloc(
		count * sizeof(VkSurfaceFormatKHR));
	assert(0 == vkGetPhysicalDeviceSurfaceFormatsKHR(
		pdev, surface, &count, formats));
	bool flag = false;
	for (uint32_t i = 0; i < count; i++) {
		if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM) {
			*format = formats[i];
			flag = true;
			break;
		}
	}
	free(formats);
	assert(flag);
}
