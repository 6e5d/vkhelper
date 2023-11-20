#include <assert.h>
#include <vulkan/vulkan.h>

#include "../include/sampler.h"

VkSampler vkhelper_sampler(VkDevice device) {
	VkSampler sampler;
	VkSamplerCreateInfo sampler_info = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
	};
	assert(0 == vkCreateSampler(device, &sampler_info,
		NULL, &sampler));
	return sampler;
}
