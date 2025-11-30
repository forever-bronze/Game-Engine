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
#include <random>


class GameEngine {
public:
  GameEngine();

  void run();
  void init();
  void load_media();

  static constexpr int width{800};
  static constexpr int height{600};

private:
  const std::string title;
  SDL_Event event;
  std::mt19937 gen;
  std::uniform_int_distribution<Uint8> rand_color;

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> background;

};