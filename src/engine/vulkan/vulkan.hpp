#pragma once
#include "common.hpp"
#include "debug.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "surface.hpp"

// The only thing that this class is doing is giving the context
class vulkan {
  instance Instance;
  debug DebugMessenger;
  surface Surface;
  physical_device PhysicalDevice;
  device Device;
  VkSwapchainKHR Swapchain{};
  VkCommandPool CommandPool{};

public:
  explicit vulkan(SDL_Window *Window)
      : Instance(Window, {"VK_LAYER_KHRONOS_validation"}), DebugMessenger{Instance.Instance},
        Surface{Window, Instance.Instance}, PhysicalDevice{Instance.Instance, Surface.Surface},
        Device{PhysicalDevice, Surface.Surface} {

        };
  inline void WithCommandBuffer(const std::function<void(VkCommandBuffer)> &Code) {};
  void Render() {}
};
