#pragma once
#include "common.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

struct instance {

public:
  VkInstance Instance{VK_NULL_HANDLE};
  instance(SDL_Window *Window, const std::vector<const char *> &ValidationLayers) {
    if (!CheckValidationLayerSupport(ValidationLayers)) {
      throw std::runtime_error("Validation layers requested but not available!");
    }
    std::vector<const char *> ExtensionNames = GetRequiredExtensions(Window);
    // TODO(lyka): Maybe I should use vkEnumerateInstanceExtensionProperties
    VkApplicationInfo AppInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Kalan Engine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };
    VkInstanceCreateInfo InstanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &AppInfo,
        .enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size()),
        .ppEnabledLayerNames = ValidationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(ExtensionNames.size()),
        .ppEnabledExtensionNames = ExtensionNames.data(),
    };
    if (vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create instance");
    }
  }

private:
  static auto CheckValidationLayerSupport(const std::vector<const char *> &ValidationLayers) -> bool {
    uint32_t LayerCount = 0;
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
    std::vector<VkLayerProperties> AvailableLayers(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

    return std::ranges::all_of(ValidationLayers, [&](const char *LayerName) {
      return std::ranges::find_if(AvailableLayers, [&](VkLayerProperties &LayerProperties) {
               return strcmp(LayerName, LayerProperties.layerName) == 0;
             }) != AvailableLayers.end();
    });
  }
  static auto GetRequiredExtensions(SDL_Window *Window,
                                    bool enableValidationLayers = true) -> std::vector<const char *> {
    uint32_t ExtensionCount = 0;
    SDL_Vulkan_GetInstanceExtensions(Window, &ExtensionCount, nullptr);
    std::vector<const char *> ExtensionNames(ExtensionCount);
    SDL_Vulkan_GetInstanceExtensions(Window, &ExtensionCount, ExtensionNames.data());

    if (enableValidationLayers) {
      ExtensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return ExtensionNames;
  }
};
