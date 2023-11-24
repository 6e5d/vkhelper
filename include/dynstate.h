#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

void vkhelper_viewport_scissor(VkCommandBuffer cbuf,
	uint32_t width, uint32_t height);
