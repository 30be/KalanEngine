#include "common.hpp"
struct debug {
  VkDebugUtilsMessengerEXT debugMessenger = nullptr;

  explicit debug(VkInstance Instance, const VkDebugUtilsMessageTypeFlagsEXT ImportanceThreshold =
                                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    static auto Threshold = ImportanceThreshold;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                              VkDebugUtilsMessageTypeFlagsEXT /*messageType*/,
                              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void * /*pUserData*/) {
          if (messageSeverity >= Threshold) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl; // Print all
          }
          return VK_FALSE;
        }};
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT"));
    if ((func == nullptr) || func(Instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
      throw std::runtime_error("failed to set up debug messenger!");
    }
  }
};
