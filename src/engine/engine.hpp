#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <cassert>
#include <iostream>
#include <thread>

#include "renderer/renderer.hpp"
class engine { // NOLINT
private:
  SDL_Window *Window;
  renderer Renderer;

public:
  engine() {
    std::cout << "Engine constructed!\n";
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      throw std::runtime_error("Failed to initialize SDL:" + std::string(SDL_GetError()));
    }
    SDL_Vulkan_LoadLibrary(nullptr);
    const int InitialWindowWidth = 1920;
    const int InitialWindowHeight = 1080;
    Window = SDL_CreateWindow("Vulkan Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, InitialWindowWidth,
                              InitialWindowHeight, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (Window == nullptr) {
      std::cout << SDL_GetError() << std::endl;
      throw std::runtime_error("Failed to create window");
    }
    Renderer = renderer(Window);
  }
  ~engine() {
    SDL_DestroyWindow(Window);
    SDL_Quit();
  }
  void Run() {
    using namespace std::chrono_literals;
    SDL_Event Event;
    bool bQuit = false;
    bool IsRendering = true;
    int frame_number = 0;
    while (!bQuit) {
      // Handle events on queue
      while (SDL_PollEvent(&Event) != 0) {
        switch (Event.type) {
        case SDL_QUIT:
          bQuit = true;
          break;
        case SDL_WINDOWEVENT:
          if (Event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
            IsRendering = false;
          }
          if (Event.window.event == SDL_WINDOWEVENT_RESTORED) {
            IsRendering = true;
          }
        }
      }
      // do not draw if we are minimized
      if (IsRendering) {
        Renderer.Render();
        std::cout << "rendered frame " << frame_number++ << std::endl;
        std::cout << "Enough. finishing";
        IsRendering = false;
      } else {
        std::this_thread::sleep_for(100ms);
      }
    }
  }
};
