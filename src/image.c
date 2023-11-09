#include <assert.h>
#include <vulkan/vulkan.h>

#include "../include/image.h"
#include "../include/memory.h"

void vkhelper_create_imageview(
	VkImageView* output,
	VkDevice device,
	VkImage image,
	VkFormat format,
	VkImageAspectFlags flags
) {
	VkImageSubresourceRange range = {
		.aspectMask = flags,
		.baseMipLevel = 0,
		.levelCount = 1,
		.baseArrayLayer = 0,
		.layerCount = 1
	};
	VkImageViewCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.subresourceRange = range,
		.image = image,
		.format = format,
	};
	assert(0 == vkCreateImageView(
		device,
		&createInfo,
		NULL,
		output
	));
}

void vkhelper_image_new(
	VkhelperImage* output,
	VkDevice device,
	VkPhysicalDeviceMemoryProperties memprop,
	uint32_t width,
	uint32_t height,
	VkFormat format
) {
	// image creation
	{
		VkImageCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = format,
			.extent = {width, height, 1},
			.mipLevels = 1,
			.arrayLayers = 1,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.tiling = VK_IMAGE_TILING_OPTIMAL,
			.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		};
		assert(0 == vkCreateImage(
			device, &info, NULL, &output->image));
	}

	// memory allocation
	VkMemoryRequirements reqs;
	vkGetImageMemoryRequirements(device, output->image, &reqs);
	VkMemoryAllocateInfo alloc = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = reqs.size,
		.memoryTypeIndex = vkhelper_memory_type_index(
			memprop,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			reqs.memoryTypeBits
		),
	};
	assert(0 == vkAllocateMemory(device, &alloc, NULL, &output->memory));
	assert(0 == vkBindImageMemory(
		device,
		output->image,
		output->memory,
		0));

	vkhelper_create_imageview(
		&output->imageview,
		device,
		output->image,
		format,
		VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT
	);
}

void vkhelper_image_destroy(VkhelperImage* image, VkDevice device) {
	vkDestroyImageView(device, image->imageview, NULL);
	vkFreeMemory(device, image->memory, NULL);
	vkDestroyImage(device, image->image, NULL);
}
