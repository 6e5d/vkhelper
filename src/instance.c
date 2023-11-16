#include <assert.h>
#include <vulkan/vulkan.h>

#include "../include/instance.h"

VkInstance vkhelper_instance(void) {
	const char* const exts[] = {
		"VK_EXT_debug_utils",
		"VK_KHR_surface",
		"VK_KHR_wayland_surface"
	};

	const char* const layerNames[] = {
		"VK_LAYER_KHRONOS_validation"
	};

	const char* appName = "vulkan";
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
		.enabledExtensionCount = sizeof(exts) / sizeof(const char*),
		.ppEnabledExtensionNames = exts,
		.enabledLayerCount = sizeof(layerNames) / sizeof(const char*),
		.ppEnabledLayerNames = layerNames,
	};

	VkInstance instance = VK_NULL_HANDLE;
	assert(0 == vkCreateInstance(&createInfo, NULL, &instance));
	return instance;
}
