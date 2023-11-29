#ifndef INCLUDEGUARD_VKHELPER_SEMAPHOREH
#define INCLUDEGUARD_VKHELPER_SEMAPHOREH

#include <vulkan/vulkan.h>

VkFence vkhelper_fence(VkDevice device);
VkSemaphore vkhelper_semaphore(VkDevice device);

#endif
