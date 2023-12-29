#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

void vkhelper(device)(
	VkDevice *device,
	VkQueue *queue,
	VkCommandPool *cpool,
	VkPhysicalDevice pdev,
	uint32_t family_idx
) {
	char *exts[1] = { "VK_KHR_swapchain" };
	char *layers[1] = { "VK_LAYER_KHRONOS_validation" };

	float priority = 1;
	VkDeviceQueueCreateInfo qinfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = family_idx,
		.queueCount = 1,
		.pQueuePriorities = &priority,
	};
	VkPhysicalDeviceDescriptorIndexingFeatures dindex = {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT,
		.shaderSampledImageArrayNonUniformIndexing = VK_TRUE,
		.descriptorBindingPartiallyBound = VK_TRUE,
		.runtimeDescriptorArray = VK_TRUE,
	};
	VkDeviceCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &dindex,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &qinfo,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = exts,
		.enabledLayerCount = 1,
		.ppEnabledLayerNames = layers,
	};
	assert(0 == vkCreateDevice(pdev, &info, NULL, device));
	vkGetDeviceQueue(*device, family_idx, 0, queue);
	VkCommandPoolCreateInfo cpool_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.queueFamilyIndex = family_idx,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	};
	assert(0 == vkCreateCommandPool(
		*device,
		&cpool_info,
		NULL,
		cpool
	));
}
