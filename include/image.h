#ifndef INCLUDEGUARD_VKHELPER_IMAGEH
#define INCLUDEGUARD_VKHELPER_IMAGEH

#include <stdbool.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

void vkhelper_create_imageview(
	VkImageView *output,
	VkDevice device,
	VkImage image,
	VkFormat format,
	VkImageAspectFlags flags,
	uint32_t mip);

typedef struct {
	VkDeviceMemory memory;
	VkImage image;
	VkImageView imageview;
	uint32_t size[2];
	uint32_t mip;
	VkImageLayout layout;
} VkhelperImage;

void vkhelper_image_new(
	VkhelperImage *output,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop,
	uint32_t width,
	uint32_t height,
	bool mip,
	VkFormat format,
	VkImageUsageFlags usage,
	VkImageAspectFlags flags);

void vkhelper_image_new_color(
	VkhelperImage *output,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop,
	uint32_t width,
	uint32_t height,
	bool mip,
	VkImageUsageFlags usage);

void vkhelper_image_new_depthstencil(
	VkhelperImage *output,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop,
	uint32_t width,
	uint32_t height,
	VkFormat format,
	VkImageUsageFlags usage);

void vkhelper_image_deinit(VkhelperImage *image, VkDevice device);

#endif
