#include <assert.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/desc.h"

void vkhelper_desc_config(VkhelperDescConf *conf, uint32_t count) {
	// 1 layout
	conf->layout_binding = (VkDescriptorSetLayoutBinding) {
		.binding = 0,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = count,
		.stageFlags = VK_SHADER_STAGE_VERTEX_BIT |
			VK_SHADER_STAGE_FRAGMENT_BIT,
	};
	conf->layout_ci = (VkDescriptorSetLayoutCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = &conf->flags_ci,
		.flags = 0,
		.bindingCount = 1,
		.pBindings = &conf->layout_binding,
	};
	conf->flags = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT;
	conf->flags_ci = (VkDescriptorSetLayoutBindingFlagsCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
		.bindingCount = 1,
		.pBindingFlags = &conf->flags,
	};
	// 2 pool
	conf->pool_size = (VkDescriptorPoolSize) {
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = count,
	};
	conf->pool_ci = (VkDescriptorPoolCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.poolSizeCount = 1,
		.pPoolSizes = &conf->pool_size,
		.maxSets = 1,
	};
	// 3 alloc
	conf->allocinfo = (VkDescriptorSetAllocateInfo) {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.descriptorSetCount = 1,
	};
}

void vkhelper_desc_build(
	VkhelperDesc *desc,
	VkhelperDescConf *conf,
	VkDevice device
) {
	assert(0 == vkCreateDescriptorSetLayout(
		device, &conf->layout_ci, NULL, &desc->layout));
	assert(0 == vkCreateDescriptorPool(
		device, &conf->pool_ci, NULL, &desc->pool));
	conf->allocinfo.descriptorPool = desc->pool;
	conf->allocinfo.pSetLayouts = &desc->layout;
	assert(0 == vkAllocateDescriptorSets(
		device, &conf->allocinfo, &desc->set));
}

void vkhelper_desc_deinit(VkhelperDesc *desc, VkDevice device) {
	vkDestroyDescriptorSetLayout(device, desc->layout, NULL);
	vkDestroyDescriptorPool(device, desc->pool, NULL);
}
