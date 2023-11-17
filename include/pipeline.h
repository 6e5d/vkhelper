#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct {
	VkPipelineShaderStageCreateInfo ss_vert;
	VkPipelineShaderStageCreateInfo ss_frag;
	VkPipelineVertexInputStateCreateInfo vis;
	VkPipelineInputAssemblyStateCreateInfo ias;
	VkPipelineViewportStateCreateInfo vsc;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineDepthStencilStateCreateInfo depthstencil;
	VkPipelineColorBlendAttachmentState cba;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineLayoutCreateInfo pl;
	VkViewport viewport;
	VkRect2D scissor;
} VkhelperPipelineConf;

void vkhelper_pipeline_configure(
	VkhelperPipelineConf *conf,
	VkShaderModule vert,
	VkShaderModule frag,
	uint32_t width,
	uint32_t height
);

void vkhelper_pipeline_standard(
	VkPipeline *pipeline,
	VkPipelineLayout *pipelinelayout,
	VkhelperPipelineConf *conf,
	VkRenderPass renderpass,
	VkDevice device,
	uint32_t subpass
);
