#include <stdint.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

VkPhysicalDevice vkhelper_pdev_selector(
	VkInstance instance,
	VkSurfaceKHR surface,
	uint32_t* result_idx
);
void vkhelper_pdev_print(VkPhysicalDevice pdev);
void vkhelper_depth_format(
	VkPhysicalDevice pdev,
	VkFormat *select
);
