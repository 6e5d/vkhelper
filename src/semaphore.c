#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

VkSemaphore vkhelper(semaphore)(VkDevice device) {
	VkSemaphore result;
	VkSemaphoreCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};
	assert(0 == vkCreateSemaphore(device, &createInfo, NULL, &result));
	return result;
}

VkFence vkhelper(fence)(VkDevice device) {
	VkFence result;
	VkFenceCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT,
	};
	assert(0 == vkCreateFence(device, &createInfo, NULL, &result));
	return result;
}
