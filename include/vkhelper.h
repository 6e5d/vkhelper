#ifndef INCLUDEGUARD_VKHELPER
#define INCLUDEGUARD_VKHELPER

#include <vulkan/vulkan.h>

VkCommandBuffer vkhelper_cbuf_new(VkCommandPool cpool, VkDevice device);

void vkhelper_device(
	VkDevice *device,
	VkQueue *queue,
	VkCommandPool *cpool,
	VkPhysicalDevice pdev,
	uint32_t family_idx
);

typedef struct {
	VkImage image;
	VkFramebuffer framebuffer;
	// first image comes from the swapchain image
	// thus has to be manually destroyed
	// second image is copied from VkhelperSwapchain.depth.imageview
	VkImageView attachments[2];
} VkhelperFramebufferImage;

VkFramebuffer vkhelper_framebuffer_create(
	VkDevice device,
	VkRenderPass renderpass,
	VkImageView *attachments,
	uint32_t width,
	uint32_t height
);

VkInstance vkhelper_instance(void);

VkPhysicalDevice vkhelper_pdev_selector(
	VkInstance instance,
	VkSurfaceKHR surface,
	uint32_t *result_idx
);
void vkhelper_pdev_print(VkPhysicalDevice pdev);
void vkhelper_depth_format(
	VkPhysicalDevice pdev,
	VkFormat *select
);

void vkhelper_scsi(
	VkSurfaceFormatKHR *format,
	VkSurfaceCapabilitiesKHR *caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

VkFence vkhelper_fence(VkDevice device);
VkSemaphore vkhelper_semaphore(VkDevice device);

VkDebugUtilsMessengerEXT vkhelper_validation_new(VkInstance instance);
void vkhelper_validation_destroy(
	VkInstance instance,
	VkDebugUtilsMessengerEXT msg
);

#endif
