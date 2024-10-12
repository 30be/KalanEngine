#include "common.hpp"
#include "physical_device.hpp"

struct swapchain {
  VkSwapchainKHR Swapchain{};
  std::vector<VkImage> SwapchainImages;
  std::vector<VkImageView> SwapchainImageViews; // TODO(lyka): Combine image and view
  VkSurfaceFormatKHR SurfaceFormat{};
  swapchain(physical_device PhysicalDevice, VkDevice Device, VkSurfaceKHR surface, VkExtent2D extent) : Device(Device) {
    physical_device::SwapChainSupportDetails SwapchainDetails = PhysicalDevice.GetSwapchainSupport(surface);
    SurfaceFormat = find_if_or(
        SwapchainDetails.formats,
        [](const auto &format) {
          return format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        },
        SwapchainDetails.formats[0]);
    VkSwapchainCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = SwapchainDetails.capabilities.minImageCount + 1,
        .imageFormat = SurfaceFormat.format,
        .imageColorSpace = SurfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .preTransform = SwapchainDetails.capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR, // TODO(lyka): Maybe use mailbox?
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };
    if (vkCreateSwapchainKHR(Device, &createInfo, nullptr, &Swapchain) != VK_SUCCESS) {
      throw std::runtime_error("failed to create swap chain!");
    }
    uint32_t ImageCount = 0;
    vkGetSwapchainImagesKHR(Device, Swapchain, &ImageCount, nullptr);
    SwapchainImages.resize(ImageCount);
    vkGetSwapchainImagesKHR(Device, Swapchain, &ImageCount, SwapchainImages.data());
  }
  ~swapchain() {
    for (auto *imageView : SwapchainImageViews) {
      vkDestroyImageView(Device, imageView, nullptr);
    }
    vkDestroySwapchainKHR(Device, Swapchain, nullptr);
  }

private:
  VkDevice Device;
  auto createImageViews() -> std::vector<VkImageView> {
    std::vector<VkImageView> SwapchainImageViews;
    for (int i = 0; i < SwapchainImages.size(); i++) {
      VkImageViewCreateInfo createInfo{
          .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
          .image = SwapchainImages[i],
          .viewType = VK_IMAGE_VIEW_TYPE_2D,
          .format = SurfaceFormat.format,
          .components =
              {
                  .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                  .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                  .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                  .a = VK_COMPONENT_SWIZZLE_IDENTITY,
              },
          .subresourceRange =
              {
                  .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                  .baseMipLevel = 0,
                  .levelCount = 1,
                  .baseArrayLayer = 0,
                  .layerCount = 1,
              },
      };
      if (vkCreateImageView(Device, &createInfo, nullptr, &SwapchainImageViews[i]) != VK_SUCCESS) {
        throw std::runtime_error("failed to create image views!");
      }
    };

    return SwapchainImageViews;
  }

public:
  swapchain(const swapchain &) = delete;
  swapchain(swapchain &&) = delete;
  auto operator=(const swapchain &) -> swapchain & = delete;
  auto operator=(swapchain &&) -> swapchain & = delete;
};
