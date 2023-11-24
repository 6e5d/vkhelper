#include <vulkan/vulkan.h>

#include "../include/barrier.h"
#include "../include/image.h"

void vkhelper_barrier(VkCommandBuffer cbuf,
	VkImageLayout old_layout,
	VkImageLayout new_layout,
	VkPipelineStageFlags src_stage,
	VkPipelineStageFlags dst_stage,
	VkhelperImage image
) {
	VkImageSubresourceRange range = {
		.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
		.levelCount = image.mip,
		.layerCount = 1,
	};
	VkImageMemoryBarrier barrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.image = image.image,
		.subresourceRange = range,
		.oldLayout = old_layout,
		.newLayout = new_layout,
	};
	vkCmdPipelineBarrier(cbuf, src_stage, dst_stage,
		0, 0, NULL, 0, NULL, 1, &barrier);
}
