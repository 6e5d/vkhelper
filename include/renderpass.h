#include <vulkan/vulkan.h>

typedef struct {
	VkRenderPassCreateInfo info;
	VkAttachmentDescription descs[2];
	VkAttachmentReference color_ref;
	VkAttachmentReference depth_ref;
} VkhelperRenderpassConf;

void vkhelper_renderpass_config(
	VkhelperRenderpassConf *conf,
	VkDevice device,
	VkFormat format,
	VkFormat depth_format
);

void vkhelper_renderpass_build(
	VkRenderPass *result,
	VkhelperRenderpassConf *conf,
	VkDevice device
);
