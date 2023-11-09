#ifndef _VKHELPER_BUFFERH
#define _VKHELPER_BUFFERH

#include <vulkan/vulkan.h>
#include <stdint.h>

typedef struct {
	VkDeviceMemory memory;
	VkBuffer buffer;
	VkDeviceSize size;
	VkDeviceMemory smemory;
	VkBuffer sbuffer;
	VkDeviceSize ssize;
} VkhelperBuffer;

void vkhelper_buffer_init(
	VkhelperBuffer* buffer,
	VkDeviceSize size,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties pdev_memprop
);

void vkhelper_buffer_deinit(
	VkhelperBuffer* buffer,
	VkDevice device
);

void vkhelper_buffer_map(
	VkDevice device,
	void* target,
	VkhelperBuffer *buffer
);

void vkhelper_buffer_unmap(VkDevice device, VkhelperBuffer *buffer);

#endif
