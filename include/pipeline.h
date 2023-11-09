#include <vulkan/vulkan.h>

typedef struct {
	VkPipelineShaderStageCreateInfo ss_vert;
	VkPipelineShaderStageCreateInfo ss_frag;
	VkPipelineVertexInputStateCreateInfo vis;
	VkPipelineInputAssemblyStateCreateInfo ias;
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo viewport_state;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineDepthStencilStateCreateInfo depthstencil;
	VkPipelineColorBlendAttachmentState cba;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineLayoutCreateInfo pl;
} VkhelperPipelineConf;

void vkhelper_pipeline_configure(
	VkhelperPipelineConf* conf,
	VkShaderModule vert,
	VkShaderModule frag
);

void vkhelper_pipeline_standard(
	VkPipeline* pipeline,
	VkPipelineLayout* pipelinelayout,
	VkhelperPipelineConf* conf,
	VkRenderPass renderpass,
	VkDevice device
);
