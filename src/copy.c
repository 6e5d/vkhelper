#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/copy.h"
#include "../include/barrier.h"

// all pixel copy, 1 image 1 layer, do image barrier before and after
// the target is used as sampler
void vkhelper_buffer_texture_copy(VkCommandBuffer cbuf,
	VkBuffer src, VkImage dst, uint32_t width, uint32_t height) {
	VkImageLayout layout1 = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	VkImageLayout layout2 = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	VkImageSubresourceLayers layers = {
		.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
		.layerCount = 1,
	};
	VkOffset3D offset = {0, 0, 0};
	VkExtent3D extent = {width, height, 1};
	VkBufferImageCopy icopy = {
		.bufferRowLength = width,
		.bufferImageHeight = height,
		.imageSubresource = layers,
		.imageOffset = offset,
		.imageExtent = extent,
	};
	vkhelper_barrier(cbuf, layout1, layout2,
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		dst);
	vkCmdCopyBufferToImage(cbuf,
		src, dst,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1, &icopy);
	vkhelper_barrier(cbuf, layout2, layout1,
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		dst);
}
