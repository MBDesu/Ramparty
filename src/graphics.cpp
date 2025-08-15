#include "graphics.h"
#include "globals.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

/**
 * Handles graphics stuff
 */
Graphics::Graphics() {
  int rendererFlags, windowFlags;
  rendererFlags = SDL_RENDERER_ACCELERATED;
  windowFlags = 0;

  SDL_Window *window = SDL_CreateWindow(
      "Ramparty", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, windowFlags);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, rendererFlags);

  if (!renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    exit(1);
  }
  this->_window = window;
  this->_renderer = renderer;
}

Graphics::~Graphics() { SDL_DestroyWindow(this->_window); }

SDL_Surface *Graphics::loadImage(const std::string &filePath) {
  if (this->_spriteSheets.count(filePath) == 0) {
    this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
  }
  return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture *source, SDL_Rect *sourceRectangle,
                           SDL_Rect *destinationRectangle) {
  SDL_RenderCopy(this->_renderer, source, sourceRectangle,
                 destinationRectangle);
}

void Graphics::flip() { SDL_RenderPresent(this->_renderer); }

void Graphics::clear() { SDL_RenderClear(this->_renderer); }

SDL_Renderer *Graphics::getRenderer() const { return this->_renderer; }
