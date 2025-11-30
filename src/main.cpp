#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include <cstdlib>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unistd.h>

#include "GameEngine.h"


void initialize_sdl() {
  int sdl_flags = SDL_INIT_EVERYTHING;
  int img_flags = IMG_INIT_PNG;

  if (SDL_Init(sdl_flags)) {
    auto error = fmt::format("error initialize SDL2: {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  if ((IMG_Init(img_flags) & img_flags) != img_flags )
  {
    auto error = fmt::format("error initialize SDL_image: {}", IMG_GetError());
    throw std::runtime_error(error);
  }

}

void close_sdl() { 
  IMG_Quit(); 
  SDL_Quit(); 
}

int main() {
  int exit_val = EXIT_SUCCESS;

  try {
    initialize_sdl();
    GameEngine gameEngine;
    gameEngine.init();
    gameEngine.load_media();
    gameEngine.run();
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    exit_val = EXIT_FAILURE;
  }

  close_sdl();

  return 0;
}