#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <cassert>
#include <iostream>
#include <thread>

#include "vulkan/vulkan.hpp"
class sdl {
public:
  SDL_Window *Window;
  sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      throw std::runtime_error("Failed to initialize SDL:" + std::string(SDL_GetError()));
    }
    Window = SDL_CreateWindow("Vulkan Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080,
                              SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Vulkan_LoadLibrary(nullptr);
    if (Window == nullptr) {
      std::cout << SDL_GetError() << std::endl;
      throw std::runtime_error("Failed to create window");
    }
  }
  sdl(const sdl &) = delete;
  sdl(sdl &&) = delete;
  auto operator=(const sdl &) -> sdl & = delete;
  auto operator=(sdl &&) -> sdl & = delete;
  ~sdl() {
    SDL_DestroyWindow(Window);
    SDL_Quit();
  }
};
class engine { // NOLINT
private:
  sdl SDL;
  vulkan Vulkan;

public:
  engine() : Vulkan{SDL.Window} { std::cout << "Engine constructed!\n"; }

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
        Vulkan.Render();
        std::cout << "rendered frame " << frame_number++ << std::endl;
        std::cout << "Enough. finishing";
        IsRendering = false;
      } else {
        std::this_thread::sleep_for(100ms);
      }
    }
  }
};
