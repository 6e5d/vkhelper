#include <vulkan/vulkan.h>

void vkhelper_device(
	VkDevice *device,
	VkQueue *queue,
	VkCommandPool *cpool,
	VkPhysicalDevice pdev,
	uint32_t family_idx
);
