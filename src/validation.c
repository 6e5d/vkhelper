#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

static VkBool32 on_error(
	VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	VkDebugUtilsMessageTypeFlagsEXT type,
	VkDebugUtilsMessengerCallbackDataEXT *callbackData,
	void *data
) {
	if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
		printf("(V");
	} else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
		printf("(I");
	} else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		printf("(W");
	} else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
		printf("(E");
	} else {
		printf("(?");
	}
	if (type == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
		printf("g)");
	} else if (type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
		printf("v) ");
	} else if (type == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
		printf("p)");
	} else {
		printf("?)");
	}

	printf("%s\n", callbackData->pMessage);
	return 0;
}

typedef union {
	PFN_vkCreateDebugUtilsMessengerEXT create;
	PFN_vkDestroyDebugUtilsMessengerEXT destroy;
	void (*empty)(void);
} VkDebugFunc;

VkDebugUtilsMessengerEXT vkhelper(validation_new)(VkInstance instance) {
	VkDebugUtilsMessengerEXT ext;
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {0};
	createInfo.sType =
		VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity =
		//VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		//VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = on_error;
	VkDebugFunc dbg;
	dbg.empty = vkGetInstanceProcAddr(instance,
		"vkCreateDebugUtilsMessengerEXT");
	assert(0 == dbg.create(instance, &createInfo, NULL, &ext));
	return ext;
}

void vkhelper(validation_destroy)(
	VkInstance instance,
	VkDebugUtilsMessengerEXT msg
) {
	VkDebugFunc dbg;
	dbg.empty = vkGetInstanceProcAddr(instance,
		"vkDestroyDebugUtilsMessengerEXT");
	dbg.destroy(instance, msg, NULL);
}
