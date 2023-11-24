#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

void vkhelper_buffer_texture_copy(VkCommandBuffer cbuf,
	VkBuffer src, VkImage dst, uint32_t width, uint32_t height);
