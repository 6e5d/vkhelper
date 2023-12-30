#include <vulkan/vulkan.h>

VkCommandBuffer vkhelper(cbuf_new)(VkCommandPool cpool, VkDevice device);

void vkhelper(device)(
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
} Vkhelper(FramebufferImage);

VkFramebuffer vkhelper(framebuffer_create)(
	VkDevice device,
	VkRenderPass renderpass,
	VkImageView *attachments,
	uint32_t width,
	uint32_t height
);

VkInstance vkhelper(instance)(void);

VkPhysicalDevice vkhelper(pdev_selector)(
	VkInstance instance,
	VkSurfaceKHR surface,
	uint32_t *result_idx
);
void vkhelper(pdev_print)(VkPhysicalDevice pdev);
void vkhelper(depth_format)(
	VkPhysicalDevice pdev,
	VkFormat *select
);

void vkhelper(scsi)(
	VkSurfaceFormatKHR *format,
	VkSurfaceCapabilitiesKHR *caps,
	VkPhysicalDevice pdev,
	VkSurfaceKHR surface
);

VkFence vkhelper(fence)(VkDevice device);
VkSemaphore vkhelper(semaphore)(VkDevice device);

VkDebugUtilsMessengerEXT vkhelper(validation_new)(VkInstance instance);
void vkhelper(validation_destroy)(
	VkInstance instance,
	VkDebugUtilsMessengerEXT msg
);
