#include "common.hpp"
#include <SDL2/SDL_vulkan.h>
struct surface {
  VkSurfaceKHR Surface = VK_NULL_HANDLE;
  surface(SDL_Window *Window, VkInstance Instance) { SDL_Vulkan_CreateSurface(Window, Instance, &Surface); }
};
