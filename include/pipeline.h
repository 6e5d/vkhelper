#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

// the motivation is for recreation based pipeline in resize handling
// we can happily save the configuration to reuse in the future
typedef struct {
	// in ppll
	VkDescriptorSetLayout *desc;

	// in in ppl
	VkVertexInputBindingDescription* vib;
	VkVertexInputAttributeDescription* via;
	VkPipelineColorBlendAttachmentState cba;
	VkDynamicState dy[2];

	VkPipelineShaderStageCreateInfo stages[2];
	VkPipelineVertexInputStateCreateInfo vis;
	VkPipelineInputAssemblyStateCreateInfo ias;
	VkPipelineViewportStateCreateInfo vs;
	VkPipelineRasterizationStateCreateInfo rast;
	VkPipelineMultisampleStateCreateInfo ms;
	VkPipelineDepthStencilStateCreateInfo dss;
	VkPipelineColorBlendStateCreateInfo cbs;
	VkPipelineDynamicStateCreateInfo dys;

	VkPipelineLayoutCreateInfo plci;
	VkGraphicsPipelineCreateInfo pci;
} VkhelperPipelineConfig;

void vkhelper_pipeline_config(VkhelperPipelineConfig *vpc,
	uint32_t vbc, uint32_t vac, uint32_t sets);
void vkhelper_pipeline_build(
	VkPipelineLayout *layout,
	VkPipeline *pipeline,
	VkhelperPipelineConfig *vpc,
	VkRenderPass renderpass,
	VkDevice device,
	uint32_t subpass
);
void vkhelper_pipeline_config_deinit(
	VkhelperPipelineConfig *vpc, VkDevice device);

void vkhelper_pipeline_simple_shader(VkhelperPipelineConfig *vpc,
	VkDevice device,
	char *src, char *relative);
