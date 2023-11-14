#ifndef INCLUDEGUARD_VKHELPER_BUFFERH
#define INCLUDEGUARD_VKHELPER_BUFFERH

#include <stdint.h>
#include <vulkan/vulkan.h>

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
