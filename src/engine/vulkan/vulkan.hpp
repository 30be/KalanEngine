#pragma once
#include "debug.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "surface.hpp"
#include "swapchain.hpp"

// The only thing that this class is doing is giving the context
class vulkan {
  instance Instance;
  debug DebugMessenger;
  surface Surface;
  physical_device PhysicalDevice;
  device Device;
  swapchain Swapchain;
  VkCommandPool CommandPool{};

public:
  explicit vulkan(SDL_Window *Window)
      : Instance(Window, {"VK_LAYER_KHRONOS_validation"}), DebugMessenger{Instance.Instance},
        Surface{Window, Instance.Instance}, PhysicalDevice{Instance.Instance, Surface.Surface},
        Device{PhysicalDevice, Surface.Surface, {VK_KHR_SWAPCHAIN_EXTENSION_NAME}},
        Swapchain{PhysicalDevice, Device.Device, Surface.Surface, {1920, 1080}} {

        };
  inline void WithCommandBuffer(const std::function<void(VkCommandBuffer)> &Code) {};
  void Render() {}
};
