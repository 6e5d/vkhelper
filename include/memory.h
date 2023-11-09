#include <vulkan/vulkan.h>
#include <stdint.h>

uint32_t vkhelper_memory_type_index(
	VkPhysicalDeviceMemoryProperties memprop,
	VkMemoryPropertyFlags props,
	uint32_t type
);
