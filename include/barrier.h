#include <vulkan/vulkan.h>

void vkhelper_barrier(VkCommandBuffer cbuf,
	VkImageLayout old_layout,
	VkImageLayout new_layout,
	VkPipelineStageFlags src_stage,
	VkPipelineStageFlags dst_stage,
	VkImage image);
