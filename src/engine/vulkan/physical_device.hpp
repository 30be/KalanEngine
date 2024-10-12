#pragma once
#include "common.hpp"
#include <algorithm>
#include <cstring>
#include <ranges>

struct physical_device {
  VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

  explicit physical_device(VkInstance instance, VkSurfaceKHR Surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    auto ExtensionsSupported = [&, this](VkPhysicalDevice device, const std::vector<const char *> &Extensions) {
      auto Extensions2 = Extensions;
      uint32_t extensionCount = 0;
      vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
      std::vector<VkExtensionProperties> availableExtensions(extensionCount);
      std::ranges::sort(Extensions2, [](const char *a, const char *b) { return strcmp(a, b) < 0; });
      std::ranges::sort(availableExtensions, [](VkExtensionProperties a, VkExtensionProperties b) -> bool {
        return strcmp(a.extensionName, b.extensionName) < 0;
      });
      vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

      return std::ranges::includes(availableExtensions |
                                       std::views::transform([](VkExtensionProperties &p) { return p.extensionName; }),
                                   Extensions2, [](const char *a, const char *b) { return strcmp(a, b) < 0; });
    };
    auto physicalDeviceIt = std::ranges::find_if(devices, [&](VkPhysicalDevice d) {
      PhysicalDevice = d;
      return GetQueueIndex(Surface) != -1 && ExtensionsSupported(d, {VK_KHR_SWAPCHAIN_EXTENSION_NAME}) &&
             GetSwapchainSupport(Surface).isok();
    }); // TODO(lyka): Replace with the best one

    if (physicalDeviceIt == devices.end()) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }
    PhysicalDevice = *physicalDeviceIt;
  }

  auto GetQueueIndex(VkSurfaceKHR Surface) const -> uint32_t {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, queueFamilies.data());
    for (int i = 0; i < queueFamilyCount; i++) {
      VkBool32 PresentSupport = VK_FALSE;
      vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &PresentSupport);

      if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0U && PresentSupport != 0) {
        return i;
      }
    }
    return -1;
  }

  struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities{};
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    [[nodiscard]] auto isok() const -> bool { return !formats.empty() && !presentModes.empty(); }
  };
  auto GetSwapchainSupport(VkSurfaceKHR surface) const -> SwapChainSupportDetails {
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, surface, &details.capabilities);

    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, surface, &formatCount, nullptr);
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, surface, &formatCount, details.formats.data());

    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, surface, &presentModeCount, nullptr);
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, surface, &presentModeCount, details.presentModes.data());

    return details;
  }
};
