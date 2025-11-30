#include "GameEngine.h"


GameEngine::GameEngine()
    : title{"Open window"}, 
      gen{},
      rand_color{0, 255},
      window{nullptr, SDL_DestroyWindow},
      renderer{nullptr, SDL_DestroyRenderer},
      background{nullptr, SDL_DestroyTexture} {}


void GameEngine::init() {
  this->window.reset(
      SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, this->width, this->height, 0));
  if (!this->window) {
    auto error = fmt::format("failed to initialize window {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->renderer.reset(
      SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (!this->renderer) {
    auto error =
        fmt::format("failed to initialize renderer {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->gen.seed(std::random_device()());
}


void GameEngine::load_media() {
  this->background.reset(IMG_LoadTexture(this->renderer.get(), "images/background.png"));

  if (!this->background) {
    auto error = fmt::format("failed to load background {}", IMG_GetError());
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
            case SDL_SCANCODE_SPACE:
              SDL_SetRenderDrawColor(this->renderer.get(), 
                  this->rand_color(gen), 
                  this->rand_color(gen), 
                  this->rand_color(gen), 255);
            break;

            default:
              break;
          }
        default:
          break;
      }
    }

    SDL_RenderClear(this->renderer.get());

    SDL_RenderCopy(this->renderer.get(), this->background.get(), nullptr, nullptr);

    SDL_RenderPresent(this->renderer.get());

    SDL_Delay(16); 
  }
}
