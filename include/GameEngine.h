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