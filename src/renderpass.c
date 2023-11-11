#include <assert.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/renderpass.h"

VkRenderPass vkhelper_renderpass(
	VkDevice device,
	VkFormat format,
	VkFormat depth_format
) {
	VkRenderPass result;
	VkAttachmentDescription attach_color = {
		.format = format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	};
	VkAttachmentDescription attach_depth = {
		.format = depth_format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	VkAttachmentDescription descs[2] = {attach_color, attach_depth};

	VkAttachmentReference color_ref = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	VkAttachmentReference depth_ref = {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	VkAttachmentReference inputs[2] = {{
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
	}, {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
	}};
	VkSubpassDescription subpass[2] = {{
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &color_ref,
		.pDepthStencilAttachment = &depth_ref,
	}, {
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.inputAttachmentCount = 2,
		.pInputAttachments = inputs,
		.colorAttachmentCount = 1,
		.pColorAttachments = &color_ref,
		.pDepthStencilAttachment = &depth_ref,
	}};
	VkSubpassDependency dependency = {
		.srcSubpass = 0,
		.dstSubpass = 1,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
		.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
	};
	VkRenderPassCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.flags = 0,
		.attachmentCount = 2,
		.pAttachments = descs,
		.subpassCount = 2,
		.pSubpasses = subpass,
		.dependencyCount = 1,
		.pDependencies = &dependency,
	};
	assert(0 == vkCreateRenderPass(
		device, &createInfo, NULL, &result));
	return result;
}
