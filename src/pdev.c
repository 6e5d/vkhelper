#include <vulkan/vulkan.h>

#include "../include/vkhelper.h"

void vkhelper_depth_format(
	VkPhysicalDevice pdev,
	VkFormat *select
) {
	static const VkFormat formats[3] = {
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM_S8_UINT,
		// only support depth + stencil
		// VK_FORMAT_D32_SFLOAT,
		// VK_FORMAT_D16_UNORM
	};
	for (size_t i = 0; i < 3; i += 1) {
		VkFormat format = formats[i];
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(pdev, format, &prop);
		if (prop.optimalTilingFeatures &
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			*select = format;
			return;
		}
	}
	printf("no suitable depth format\n");
	abort();
}

static bool check_device_surface_support(
	VkPhysicalDevice pdev, VkSurfaceKHR surface, uint32_t *idx
) {
	uint32_t count;
	vkGetPhysicalDeviceQueueFamilyProperties(pdev, &count, NULL);
	VkBool32 flag = VK_FALSE;
	typedef VkQueueFamilyProperties Prop;
	Prop *families = malloc(sizeof(Prop)  *count);
	vkGetPhysicalDeviceQueueFamilyProperties(pdev, &count, families);
	uint32_t j = 0;
	for (; j < count; j+=1) {
		VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(
			pdev,
			j,
			surface,
			&flag
		);
		if ((result == VK_SUCCESS) &&
			(flag == VK_TRUE) &&
			(families[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		) {
			break;
		}
	}
	free(families);
	if (j == count) {
		return false;
	}
	*idx = j;
	return true;
}

VkPhysicalDevice vkhelper_pdev_selector(
	VkInstance instance,
	VkSurfaceKHR surface,
	uint32_t *result_idx
) {
	uint32_t devcount;
	vkEnumeratePhysicalDevices(instance, &devcount, NULL);
	VkPhysicalDevice *pdevs = malloc(devcount  *sizeof(VkPhysicalDevice));

	vkEnumeratePhysicalDevices(
		instance,
		&devcount,
		pdevs
	);
	VkPhysicalDevice result = VK_NULL_HANDLE;
	int32_t best_score = -1;
	uint32_t best_idx = 0;
	for (uint32_t i = 0; i < devcount; i++) {
		VkPhysicalDevice pdev = pdevs[i];
		uint32_t family_idx;
		if (!check_device_surface_support(pdev, surface, &family_idx)) {
			continue;
		}
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(pdev, &properties);
		int32_t score;
		switch (properties.deviceType) {
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			score = 4;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			score = 3;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			score = 2;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			score = 1;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			score = 0;
			break;
		default:
			printf("unknown device type\n");
			abort();
		}
		if (score > best_score) {
			result = pdev;
			best_score = score;
			best_idx = family_idx;
		}
	}
	assert(best_score >= 0);
	free(pdevs);
	*result_idx = best_idx;
	return result;
}

void vkhelper_pdev_print(VkPhysicalDevice pdev) {
	VkPhysicalDeviceProperties prop;
	vkGetPhysicalDeviceProperties(pdev, &prop);
	// printf("api version: %d\n", prop.apiVersion);
	// printf("driver version: %d\n", prop.driverVersion);
	// printf("vendor id: %d\n", prop.vendorID);
	// printf("device id: %d\n", prop.deviceID);
	printf("device name: %s\n", prop.deviceName);
}
