#ifndef INCLUDEGUARD_VKHELPER_DEVICEH
#define INCLUDEGUARD_VKHELPER_DEVICEH

#include <vulkan/vulkan.h>

void vkhelper_device(
	VkDevice *device,
	VkQueue *queue,
	VkCommandPool *cpool,
	VkPhysicalDevice pdev,
	uint32_t family_idx
);

#endif
