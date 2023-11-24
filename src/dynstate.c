#include <stdint.h>
#include <vulkan/vulkan.h>

#include "../include/dynstate.h"

void vkhelper_viewport_scissor(VkCommandBuffer cbuf,
	uint32_t width, uint32_t height
) {
	VkViewport viewport = {0.0f, 0.0f,
		(float)width, (float)height,
		0.0f, 1.0f};
	VkRect2D scissor = {{0.0f, 0.0f}, {width, height}};
	vkCmdSetViewport(cbuf, 0, 1, &viewport);
	vkCmdSetScissor(cbuf, 0, 1, &scissor);
}
