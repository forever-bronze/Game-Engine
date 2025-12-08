#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
  void update_text();
  void update_sprite();


  const std::string title;
  SDL_Event event;
  std::mt19937 gen;
  std::uniform_int_distribution<Uint8> rand_color;

  int font_size;
  SDL_Color font_color;
  std::string text_str;
  SDL_Rect text_rect;
  const int text_vel;
  int text_xvel;
  int text_yvel;

  SDL_Rect sprite_rect;
  const int sprite_vel;


  const Uint8 *keystate;


  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> background;
  
  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> text_surface;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> text;

  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> icon_surface;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> sprite;


};