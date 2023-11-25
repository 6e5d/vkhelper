#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../../dmgrect/include/dmgrect.h"
#include "image.h"

void vkhelper_buffer_texture_copy(VkCommandBuffer cbuf,
	VkBuffer src, VkhelperImage *dst, Dmgrect *rect);
