#include "GameEngine.h"


GameEngine::GameEngine()
    : title{"Open window"}, 
      gen{}, rand_color{0, 255}, font_size{80},
      font_color{255, 255, 255, 255}, text_str("SDL"), text_rect{0, 0, 0, 0},
      keystate{SDL_GetKeyboardState(nullptr)},
      window{nullptr, SDL_DestroyWindow},
      renderer{nullptr, SDL_DestroyRenderer},
      background{nullptr, SDL_DestroyTexture},
      font{nullptr, TTF_CloseFont},
      text_surface{nullptr, SDL_FreeSurface},
      text{nullptr, SDL_DestroyTexture},
      text_vel{3}, text_xvel{3}, text_yvel{3},
      icon_surface{nullptr, SDL_FreeSurface}, 
      sprite_rect{0, 0, 0, 0}, sprite_vel(5), sprite{nullptr, SDL_DestroyTexture},
      cpp_sound{nullptr, Mix_FreeChunk}, sdl_sound{nullptr, Mix_FreeChunk},
      music{nullptr, Mix_FreeMusic}
{

}

GameEngine::~GameEngine() {
  Mix_HaltChannel(-1);
  Mix_HaltMusic();
}


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
    auto error = fmt::format("failed to initialize renderer {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->icon_surface.reset(IMG_Load("images/Cpp-logo.png"));
  if (!this->window) {
    auto error = fmt::format("failed to load Surface {}", IMG_GetError());
    throw std::runtime_error(error);
  }  

  SDL_SetWindowIcon(this->window.get(), this->icon_surface.get());

  this->gen.seed(std::random_device()());
}


void GameEngine::load_media() {
  this->background.reset(IMG_LoadTexture(this->renderer.get(), "images/background.png"));
  if (!this->background) {
    auto error = fmt::format("failed to load background {}", IMG_GetError());
    throw std::runtime_error(error);
  }

  this->font.reset(TTF_OpenFont("fonts/freesansbold.ttf", this->font_size));
  if (!this->font) {
    auto error = fmt::format("failed to load font {}", TTF_GetError());
    throw std::runtime_error(error);
  }

  this->text_surface.reset(TTF_RenderText_Blended(this->font.get(), this->text_str.c_str(), this->font_color));
  if (!this->text_surface) {
    auto error = fmt::format("failed to load text surface {}", TTF_GetError());
    throw std::runtime_error(error);
  }

  this->text_rect.w = this->text_surface->w;
  this->text_rect.h = this->text_surface->h;
  
  this->text.reset(SDL_CreateTextureFromSurface(this->renderer.get(), this->text_surface.get()));
  if (!this->text) {
    auto error = fmt::format("failed to create Texture from Surface {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->sprite_rect.w = this->icon_surface->w;
  this->sprite_rect.h = this->icon_surface->h;

  this->sprite.reset(SDL_CreateTextureFromSurface(this->renderer.get(), this->icon_surface.get()));
  if (!this->sprite) {
    auto error = fmt::format("failed to create Texture from Surface {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  if (SDL_QueryTexture(this->sprite.get(), nullptr, nullptr, &this->sprite_rect.w, &this->sprite_rect.h)) {
    auto error = fmt::format("failed to query Texture {}", SDL_GetError());
    throw std::runtime_error(error);
  } 

  this->cpp_sound.reset(Mix_LoadWAV("sounds/Cpp.ogg"));
  if (!this->cpp_sound) {
    auto error = fmt::format("failed to load Chunk {}", Mix_GetError());
    throw std::runtime_error(error);
  }

  this->sdl_sound.reset(Mix_LoadWAV("sounds/SDL.ogg"));
  if (!this->sdl_sound) {
    auto error = fmt::format("failed to load Chunk {}", Mix_GetError());
    throw std::runtime_error(error);
  }

  this->music.reset(Mix_LoadMUS("music/freesoftwaresong-8bit.ogg"));
  if (!this->music) {
    auto error = fmt::format("failed to load music {}", Mix_GetError());
    throw std::runtime_error(error);
  }

}

void GameEngine::update_text() {
  this->text_rect.x += this->text_xvel;
  this->text_rect.y += this->text_yvel;

  if (this->text_rect.x < 0 || this->text_rect.x + this->text_rect.w > this->width) {
    this->text_xvel = -this->text_xvel;
    Mix_PlayChannel(-1, this->sdl_sound.get(), 0);
  }

  if (this->text_rect.y < 0 || this->text_rect.y + this->text_rect.h > this->height) {
    this->text_yvel = -this->text_yvel;
    Mix_PlayChannel(-1, this->sdl_sound.get(), 0);
  }
  
}

void GameEngine::update_sprite() {
  if (this->keystate[SDL_SCANCODE_LEFT] || this->keystate[SDL_SCANCODE_A]) {
    this->sprite_rect.x -= this->sprite_vel;
  }
  if (this->keystate[SDL_SCANCODE_RIGHT] || this->keystate[SDL_SCANCODE_D]) {
    this->sprite_rect.x += this->sprite_vel;
  }
  if (this->keystate[SDL_SCANCODE_UP] || this->keystate[SDL_SCANCODE_W]) {
    this->sprite_rect.y -= this->sprite_vel;
  }
  if (this->keystate[SDL_SCANCODE_DOWN] || this->keystate[SDL_SCANCODE_S]) {
    this->sprite_rect.y += this->sprite_vel;
  }
}

void GameEngine::run() {
  if (Mix_PlayMusic(this->music.get(), -1)) {
    auto error = fmt::format("failed to play music {}", Mix_GetError());
    throw std::runtime_error(error);
  }
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
                  this->rand_color(this->gen), 
                  this->rand_color(this->gen), 
                  this->rand_color(this->gen), 255);
              Mix_PlayChannel(-1, this->cpp_sound.get(), 0);
              break;

            case SDL_SCANCODE_M:
              Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
              break;


            default:
              break;
          }
        default:
          break;
      }
    }

    this->update_text();
    this->update_sprite();

    SDL_RenderClear(this->renderer.get());

    SDL_RenderCopy(this->renderer.get(), this->background.get(), nullptr, nullptr);

    SDL_RenderCopy(this->renderer.get(), this->text.get(), nullptr, &this->text_rect);

    SDL_RenderCopy(this->renderer.get(), this->sprite.get(), nullptr, &this->sprite_rect);

    SDL_RenderPresent(this->renderer.get());

    SDL_Delay(16); 
  }
}
