#include <vulkan/vulkan.h>

VkDebugUtilsMessengerEXT vkhelper_validation_new(VkInstance instance);
void vkhelper_validation_destroy(
	VkInstance instance,
	VkDebugUtilsMessengerEXT msg
);
