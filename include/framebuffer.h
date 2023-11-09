#ifndef _VKBASIC_FRAMEBUFFERH
#define _VKBASIC_FRAMEBUFFERH

#include <vulkan/vulkan.h>

typedef struct {
	VkImage image;
	VkFramebuffer framebuffer;
	// first image comes from the swapchain image
	// thus has to be manually destroyed
	// second image is copied from VkhelperSwapchain.depth.imageview
	VkImageView attachments[2];
} VkhelperFramebufferImage;

VkFramebuffer create_framebuffer(
	VkDevice device,
	VkRenderPass renderpass,
	VkImageView* attachments,
	uint32_t width,
	uint32_t height
);

#endif
