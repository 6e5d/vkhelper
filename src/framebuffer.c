#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#include "../include/framebuffer.h"
#include "../include/image.h"

VkFramebuffer create_framebuffer(
	VkDevice device,
	VkRenderPass renderpass,
	VkImageView* attachments,
	uint32_t width,
	uint32_t height
) {
	VkFramebuffer framebuffer;
	VkFramebufferCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.renderPass = renderpass,
		.attachmentCount = 2,
		.pAttachments = attachments,
		.width = width,
		.height = height,
		.layers = 1,
	};
	assert(0 == vkCreateFramebuffer(
		device, &createInfo, NULL, &framebuffer));
	return framebuffer;
}
