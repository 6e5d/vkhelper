#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#include "../include/shader.h"
#include "../../wholefile/include/wholefile.h"

VkShaderModule vkhelper_shader_module(
	VkDevice device,
	char* path
) {
	uint32_t* data;
	size_t len = wholefile_read(path, (uint8_t**)&data);
	if (len % 4 != 0) {
		printf("bad spv shader code!\n");
		exit(1);
	}
	VkShaderModuleCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = len,
		.pCode = data,
	};
	VkShaderModule shaderModule;
	assert(0 == vkCreateShaderModule(
		device, &createInfo, NULL, &shaderModule));
	// printf("loaded: %s\n", path);
	free(data);
	return shaderModule;
}
