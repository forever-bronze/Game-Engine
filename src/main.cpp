
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cstdlib>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unistd.h>

class GameEngine {
public:
  GameEngine();

  void run();
  void init();

  static constexpr int width{800};
  static constexpr int height{600};

private:
  const std::string title;

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};

GameEngine::GameEngine()
    : title{"Open window"}, window{nullptr, SDL_DestroyWindow},
      renderer{nullptr, SDL_DestroyRenderer} {}

void GameEngine::init() {
  this->window.reset(
      SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, this->width, this->height, 0));
  if (!this->window) {
    // format is a c++20 feature make sure to include -std=c++20 flag with g++
    auto error = fmt::format("failed to initialize window {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->renderer.reset(
      SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (!this->renderer) {
    // format is a c++20 feature make sure to include -std=c++20 flag with g++
    auto error =
        fmt::format("failed to initialize renderer {}", SDL_GetError());
    throw std::runtime_error(error);
  }
}

void initialize_sdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    auto error = fmt::format("error handling SDL2: {}", SDL_GetError());
    throw std::runtime_error(error);
  }
}

void close_sdl() { SDL_Quit(); }

void GameEngine::run() { SDL_Delay(2000); }

int main() {
  int exit_val = EXIT_SUCCESS;

  try {
    initialize_sdl();
    GameEngine gameEngine;
    gameEngine.init();
    gameEngine.run();
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    exit_val = EXIT_FAILURE;
  }
  close_sdl();

  return 0; // Added missing semicolon
}
