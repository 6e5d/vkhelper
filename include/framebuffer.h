#ifndef INCLUDEGUARD_VKBASIC_FRAMEBUFFERH
#define INCLUDEGUARD_VKBASIC_FRAMEBUFFERH

#include <vulkan/vulkan.h>

typedef struct {
	VkImage image;
	VkFramebuffer framebuffer;
	// first image comes from the swapchain image
	// thus has to be manually destroyed
	// second image is copied from VkhelperSwapchain.depth.imageview
	VkImageView attachments[2];
} VkhelperFramebufferImage;

VkFramebuffer vkhelper_framebuffer_create(
	VkDevice device,
	VkRenderPass renderpass,
	VkImageView *attachments,
	uint32_t width,
	uint32_t height
);

#endif
