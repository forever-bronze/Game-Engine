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
#include <GameEngine.h>


void initialize_sdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    auto error = fmt::format("error handling SDL2: {}", SDL_GetError());
    throw std::runtime_error(error);
  }
}

void close_sdl() { SDL_Quit(); }

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
