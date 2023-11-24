// a simple descriptor set manager
// 1 pool -> 1 set -> 1 binding
// * create layout
// * create pool
// * allocate descset

#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct {
	VkDescriptorSetLayoutBinding *bindings;
	VkDescriptorSetLayoutCreateInfo layout_ci;
	VkDescriptorPoolSize *sizes;
	VkDescriptorPoolCreateInfo pool_ci;
	VkDescriptorSetAllocateInfo allocinfo;
} VkhelperDescConfig;

typedef struct {
	VkDescriptorSetLayout layout;
	VkDescriptorPool pool;
	VkDescriptorSet set;
} VkhelperDesc;

// only for single image
void vkhelper_desc_write_image(
	VkWriteDescriptorSet *write,
	VkDescriptorImageInfo *info,
	VkDescriptorSet set,
	VkImageView imageview,
	VkSampler sampler,
	uint32_t binding);
// default config for uniform buffer
void vkhelper_desc_config(VkhelperDescConfig *conf, uint32_t bcount);
void vkhelper_desc_config_image(VkhelperDescConfig *conf, size_t idx);
void vkhelper_desc_config_deinit(VkhelperDescConfig *conf);
void vkhelper_desc_build(
	VkhelperDesc *desc,
	VkhelperDescConfig *conf,
	VkDevice device
);
void vkhelper_desc_deinit(VkhelperDesc *desc, VkDevice device);
