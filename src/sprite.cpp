#include "sprite.h"
#include "globals.h"
#include "graphics.h"

#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int srcX,
               int srcY, int w, int h, float posX, float posY)
    : _x(posX), _y(posY) {
  this->_sourceRect.x = srcX;
  this->_sourceRect.y = srcY;
  this->_sourceRect.w = w;
  this->_sourceRect.h = h;
  this->_spriteSheet = SDL_CreateTextureFromSurface(
      graphics.getRenderer(), graphics.loadImage(filePath));
  if (this->_spriteSheet == NULL) {
    std::cerr << "Unable to load image: " << filePath << std::endl;
  }
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
  SDL_Rect destinationRectangle = {
      x, y, static_cast<int>(this->_sourceRect.w * globals::SPRITE_SCALE),
      static_cast<int>(this->_sourceRect.h * globals::SPRITE_SCALE)};
  graphics.blitSurface(this->_spriteSheet, &this->_sourceRect,
                       &destinationRectangle);
}

void Sprite::update() {}
