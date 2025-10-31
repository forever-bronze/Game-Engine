
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <memory>
#include <stdexcept>

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
};

GameEngine::GameEngine()
    : title{"Open window"}, window{nullptr, SDL_DestroyWindow} {}

void GameEngine::init() {
  this->window.reset(
      SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, this->width, this->height, 0));
  if (!this->window) {
    // format is a c++20 feature make sure to include -std=c++20 flag with g++
    auto error = std::format("failed to initialize window {}", SDL_GetError());
    throw std::runtime_error(error);
  }
}

int main() {
  // Corrected SDL types (capital W and R)
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  // Corrected SDL constant (underscores and uppercase)
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL could not initialize! Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // Create window
  window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (!window) {
    std::cout << "Window could not be created! Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    std::cout << "Renderer could not be created! Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  std::cout << "SDL initialized successfully!" << std::endl;

  while (true) {
    char input;
    std::cout << "quit with q :" << "\n";
    std::cout << "     -input: ";
    std::cin >> input;

    if (input == 'q') {
      // Cleanup
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      std::cout << "Closed the Window";
      break;
    } else {
      continue;
    }
  }

  return 0; // Added missing semicolon
}
