#include "GameEngine.h"


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


void GameEngine::run() { 
  while (true) {
    while (SDL_PollEvent(&this->event)) {
      switch (event.type) {
        case SDL_QUIT:
          return;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
              return;
              break;
            default:
              break;
          }
        default:
          break;
      }
    }

    SDL_RenderClear(this->renderer.get());

    SDL_RenderPresent(this->renderer.get());

    SDL_Delay(16); 
  }
}
