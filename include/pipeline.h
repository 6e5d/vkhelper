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
	VkPipelineDynamicStateCreateInfo dsi;
	VkDynamicState dss[2];
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
