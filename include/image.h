#ifndef VKBASIC_IMAGEH
#define VKBASIC_IMAGEH

#include <vulkan/vulkan.h>

void vkhelper_create_imageview(
	VkImageView* output,
	VkDevice device,
	VkImage image,
	VkFormat format,
	VkImageAspectFlags flags
);

typedef struct {
	VkImage image;
	VkDeviceMemory memory;
	VkImageView imageview;
} VkhelperImage;

void vkhelper_image_new(
	VkhelperImage* output,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop,
	uint32_t width,
	uint32_t height,
	VkFormat format,
	VkImageUsageFlags usage,
	VkImageAspectFlags flags);

void vkhelper_image_deinit(VkhelperImage* image, VkDevice device);

#endif
