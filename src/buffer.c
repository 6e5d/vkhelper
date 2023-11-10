#include <assert.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/buffer.h"
#include "../include/memory.h"

// render buffer
void vkhelper_buffer_init(
	VkhelperBuffer* buffer,
	VkDeviceSize size,
	VkBufferUsageFlags flags,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop
) {
	// buffer
	VkBufferCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = size,
		.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT, // staging
	};
	assert(0 == vkCreateBuffer(device, &info, NULL, &buffer->sbuffer));

	// memory
	VkMemoryRequirements reqs;
	vkGetBufferMemoryRequirements(device, buffer->sbuffer, &reqs);
	buffer->ssize = reqs.size;
	uint32_t mti = vkhelper_memory_type_index(
		memprop,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		reqs.memoryTypeBits
	);
	VkMemoryAllocateInfo alloc_info = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = reqs.size,
		.memoryTypeIndex = mti,
	};
	assert(0 == vkAllocateMemory(
		device, &alloc_info, NULL, &buffer->smemory));

	info.usage = flags | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	assert(0 == vkCreateBuffer(
		device, &info, NULL, &buffer->buffer));
	vkGetBufferMemoryRequirements(device, buffer->buffer, &reqs);
	buffer->size = reqs.size;
	mti = vkhelper_memory_type_index(
		memprop,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		reqs.memoryTypeBits
	);
	alloc_info = (VkMemoryAllocateInfo) {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = reqs.size,
		.memoryTypeIndex = mti,
	};
	assert(0 == vkAllocateMemory(
		device, &alloc_info, NULL, &buffer->memory));
	assert(0 == vkBindBufferMemory(
		device, buffer->buffer, buffer->memory, 0));
}

void vkhelper_buffer_deinit(
	VkhelperBuffer* buffer,
	VkDevice device
) {
	vkDestroyBuffer(device, buffer->buffer, NULL);
	vkFreeMemory(device, buffer->memory, NULL);
	vkDestroyBuffer(device, buffer->sbuffer, NULL);
	vkFreeMemory(device, buffer->smemory, NULL);
}

void vkhelper_buffer_map(
	VkDevice device,
	void** target,
	VkhelperBuffer* buffer
) {
	assert(0 == vkMapMemory(
		device, buffer->smemory, 0, buffer->ssize, 0, target));
}

void vkhelper_buffer_unmap(VkDevice device, VkhelperBuffer *buffer) {
	vkUnmapMemory(device, buffer->smemory);
	assert(0 == vkBindBufferMemory(
		device, buffer->sbuffer, buffer->smemory, 0));
}

// sync, so it is slow, for initialization only
void vkhelper_buffer_sync(
	VkhelperBuffer* buf,
	VkDeviceSize size,
	VkDevice device,
	VkQueue queue,
	VkCommandPool cpool
) {
	VkCommandBuffer copyCmd;
	VkCommandBufferAllocateInfo cmdBufAllocateInfo = {
		.sType =
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = cpool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1,
	};
	assert(0 == vkAllocateCommandBuffers(
		device, &cmdBufAllocateInfo, &copyCmd));

	VkCommandBufferBeginInfo cmdBufInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
	};
	assert(0 == vkBeginCommandBuffer(copyCmd, &cmdBufInfo));
	VkBufferCopy copyRegion = {.size = size};
	vkCmdCopyBuffer(copyCmd, buf->sbuffer, buf->buffer,
		1, &copyRegion);
	assert(0 == vkEndCommandBuffer(copyCmd));

	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.commandBufferCount = 1,
		.pCommandBuffers = &copyCmd,
	};

	// Create fence to ensure that the command buffer has finished executing
	VkFenceCreateInfo fenceCI = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = 0,
	};
	VkFence fence;
	assert(0 == vkCreateFence(device, &fenceCI, NULL, &fence));
	assert(0 == vkQueueSubmit(queue, 1, &submitInfo, fence));
	assert(0 == vkWaitForFences(device, 1, &fence, VK_TRUE, 1000000000));

	vkDestroyFence(device, fence, NULL);
	vkFreeCommandBuffers(device, cpool, 1, &copyCmd);
}
