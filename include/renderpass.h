#include <vulkan/vulkan.h>

typedef struct {
	VkRenderPassCreateInfo info;
	VkAttachmentDescription descs[2];
	VkAttachmentReference color_ref;
	VkAttachmentReference depth_ref;
	VkSubpassDescription subpass;
} VkhelperRenderpassConfig;

void vkhelper_renderpass_config_offscreen(
	VkhelperRenderpassConfig *conf,
	VkDevice device
);

void vkhelper_renderpass_config(
	VkhelperRenderpassConfig *conf,
	VkDevice device,
	VkFormat format,
	VkFormat depth_format
);

void vkhelper_renderpass_build(
	VkRenderPass *result,
	VkhelperRenderpassConfig *conf,
	VkDevice device
);
