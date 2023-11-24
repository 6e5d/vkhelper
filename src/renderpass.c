#include <assert.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/renderpass.h"

void vkhelper_renderpass_config_offscreen(
	VkhelperRenderpassConfig *conf,
	VkDevice device) {
	VkAttachmentDescription attach_color = {
		.format = VK_FORMAT_B8G8R8A8_UNORM,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
	};
	conf->descs[0] = attach_color;

	conf->color_ref = (VkAttachmentReference) {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};

	conf->subpass = (VkSubpassDescription) {
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &conf->color_ref,
	};

	conf->info = (VkRenderPassCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.flags = 0,
		.attachmentCount = 1,
		.pAttachments = conf->descs,
		.subpassCount = 1,
		.pSubpasses = &conf->subpass,
	};
}

void vkhelper_renderpass_config(
	VkhelperRenderpassConfig *conf,
	VkDevice device,
	VkFormat format,
	VkFormat depth_format
) {
	VkAttachmentDescription attach_color = {
		.format = format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	};
	VkAttachmentDescription attach_depth = {
		.format = depth_format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	conf->descs[0] = attach_color;
	conf->descs[1] = attach_depth;

	conf->color_ref = (VkAttachmentReference) {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	conf->depth_ref = (VkAttachmentReference) {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};

	conf->subpass = (VkSubpassDescription) {
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &conf->color_ref,
		.pDepthStencilAttachment = &conf->depth_ref,
	};

	conf->info = (VkRenderPassCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.flags = 0,
		.attachmentCount = 2,
		.pAttachments = conf->descs,
		.subpassCount = 1,
		.pSubpasses = &conf->subpass,
		.dependencyCount = 0,
		.pDependencies = NULL,
	};
}

void vkhelper_renderpass_build(
	VkRenderPass *result,
	VkhelperRenderpassConfig *conf,
	VkDevice device) {
	assert(0 == vkCreateRenderPass(device, &conf->info, NULL, result));
}
