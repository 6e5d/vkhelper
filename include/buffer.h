#ifndef INCLUDEGUARD_VKHELPER_BUFFERH
#define INCLUDEGUARD_VKHELPER_BUFFERH

#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct {
	VkDeviceMemory memory;
	VkBuffer buffer;
	VkDeviceSize size; // original
} VkhelperBuffer;

void vkhelper_buffer_init_cpu(
	VkhelperBuffer* buffer,
	VkDeviceSize size,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties pdev_memprop
);

void vkhelper_buffer_init_gpu(
	VkhelperBuffer* buffer,
	VkDeviceSize size,
	VkBufferUsageFlags flags,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties pdev_memprop
);

void vkhelper_buffer_deinit(
	VkhelperBuffer* buffer,
	VkDevice device
);

#endif
