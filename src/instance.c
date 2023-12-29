#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

VkInstance vkhelper(instance)(void) {
	char *exts[3] = {
		"VK_EXT_debug_utils",
		"VK_KHR_surface",
		"VK_KHR_wayland_surface"
	};

	char *layerNames[1] = {
		"VK_LAYER_KHRONOS_validation"
	};

	char *appName = "vulkan";
	VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = appName,
		.applicationVersion = VK_MAKE_VERSION(0, 1, 0),
		.pEngineName = appName,
		.engineVersion = VK_MAKE_VERSION(0, 1, 0),
		.apiVersion = VK_API_VERSION_1_2,
	};

	VkInstanceCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
		.enabledExtensionCount = 3,
		.ppEnabledExtensionNames = exts,
		.enabledLayerCount = 1,
		.ppEnabledLayerNames = layerNames,
	};

	VkInstance instance = VK_NULL_HANDLE;
	assert(0 == vkCreateInstance(&createInfo, NULL, &instance));
	return instance;
}
