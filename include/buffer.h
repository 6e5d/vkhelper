#ifndef _VKHELPER_BUFFERH
#define _VKHELPER_BUFFERH

#include <vulkan/vulkan.h>
#include <stdint.h>

typedef struct {
	VkDeviceSize real_size;
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
	VkBufferUsageFlags flags,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties pdev_memprop
);

void vkhelper_buffer_deinit(
	VkhelperBuffer* buffer,
	VkDevice device
);

void vkhelper_buffer_sync(
	VkhelperBuffer* buf,
	VkDeviceSize size,
	VkDevice device,
	VkQueue queue,
	VkCommandPool cpool
);

#endif