// a simple descriptor set manager
// 1 pool -> 1 set -> 1 binding
// * create layout
// * create pool
// * allocate descset

#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct {
	VkDescriptorSetLayoutBinding layout_binding;
	VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci;
	VkDescriptorSetLayoutCreateInfo layout_ci;
	VkDescriptorPoolSize pool_size;
	VkDescriptorPoolCreateInfo pool_ci;
	VkDescriptorSetAllocateInfo allocinfo;
	VkDescriptorBindingFlags flags;
} VkhelperDescConf;

typedef struct {
	VkDescriptorSetLayout layout;
	VkDescriptorPool pool;
	VkDescriptorSet set;
} VkhelperDesc;

// default config for uniform buffer
void vkhelper_desc_config(VkhelperDescConf *conf, uint32_t count);
void vkhelper_desc_build(
	VkhelperDesc *desc,
	VkhelperDescConf *conf,
	VkDevice device
);
void vkhelper_desc_deinit(VkhelperDesc *desc, VkDevice device);
