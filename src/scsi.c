#include <assert.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

#include "../include/scsi.h"

VkhelperScsi vkhelper_scsi(
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
) {
	VkhelperScsi result;
	assert(0 == vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		pdev, surface, &result.caps));
	uint32_t formatCount;
	assert(0 == vkGetPhysicalDeviceSurfaceFormatsKHR(
		pdev, surface, &formatCount, NULL));
	VkSurfaceFormatKHR formats[formatCount];
	assert(0 == vkGetPhysicalDeviceSurfaceFormatsKHR(
		pdev, surface, &formatCount, formats));
	bool flag = false;
	for (uint32_t i = 0; i < formatCount; i++) {
		if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM) {
			result.format = formats[i];
			flag = true;
			break;
		}
	}
	assert(flag);
	return result;
}
