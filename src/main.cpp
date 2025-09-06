
#include <iostream>
#include <SDL.h>

int main() {
  // Corrected SDL types (capital W and R)
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  
  // Corrected SDL constant (underscores and uppercase)
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  
  // Create window
  window = SDL_CreateWindow("Game Engine", 
                           SDL_WINDOWPOS_CENTERED, 
                           SDL_WINDOWPOS_CENTERED, 
                           800, 600, 
                           SDL_WINDOW_SHOWN);
  
  if (!window) {
    std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
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

  
  return 0;  // Added missing semicolon
}
