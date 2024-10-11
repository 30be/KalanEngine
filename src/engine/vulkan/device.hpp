#pragma once
#include "common.hpp"
#include "physical_device.hpp"

// TODO(lyka): Add support for multiple queue families
struct device {
  VkDevice Device = VK_NULL_HANDLE;
  VkQueue GraphicsQueue = VK_NULL_HANDLE;
  device(const device &) = delete;
  device(device &&) = delete;
  auto operator=(const device &) -> device & = delete;
  auto operator=(device &&) -> device & = delete;
  explicit device(physical_device PhysicalDevice, VkSurfaceKHR Surface, std::vector<const char *> deviceExtensions) {
    float queuePriority = 1.0F;
    uint32_t QueueFamilyIndex = PhysicalDevice.GetQueueIndex(Surface);
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceQueueCreateInfo queueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = QueueFamilyIndex, // TODO(lyka): Choose the best on,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    };

    VkDeviceCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .ppEnabledLayerNames = deviceExtensions.data(),
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .pEnabledFeatures = &deviceFeatures,
    };
    if (vkCreateDevice(PhysicalDevice.PhysicalDevice, &createInfo, nullptr, &Device) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device!");
    }
    vkGetDeviceQueue(Device, QueueFamilyIndex, 0, &GraphicsQueue);
  };
  ~device() { vkDestroyDevice(Device, nullptr); };
};
