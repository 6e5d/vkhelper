#ifndef INCLUDEGUARD_VKHELPER_CBUFH
#define INCLUDEGUARD_VKHELPER_CBUFH

#include <vulkan/vulkan.h>

VkCommandBuffer vkhelper_cbuf_new(VkCommandPool cpool, VkDevice device);

#endif
