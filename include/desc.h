// a simple descriptor set manager
// 1 pool -> 1 set -> 1 binding
// * create layout
// * create pool
// * allocate descset

#pragma once

#include <vulkan/vulkan.h>

typedef struct {
	VkDescriptorSetLayoutBinding layout_binding;
	VkDescriptorSetLayoutCreateInfo layout_ci;
	VkDescriptorPoolSize pool_size;
	VkDescriptorPoolCreateInfo pool_ci;
	VkDescriptorSetAllocateInfo allocinfo;
} VkhelperDescConf;

typedef struct {
	VkDescriptorSetLayout layout;
	VkDescriptorPool pool;
	VkDescriptorSet set;
} VkhelperDesc;

// default config for uniform buffer
void vkhelper_desc_config(VkhelperDescConf *conf);
void vkhelper_desc_build(
	VkhelperDesc *desc,
	VkhelperDescConf *conf,
	VkDevice device
);
void vkhelper_desc_deinit(VkhelperDesc *desc, VkDevice device);
