#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <SDL.h>

struct Graphics; // forward declaration

class Sprite {
public:
  Sprite();
  Sprite(Graphics &graphics, const std::string &filePath, int srcX, int srcY,
         int w, int h, float posX, float posY);
  virtual ~Sprite();
  virtual void update();
  void draw(Graphics &graphics, int x, int y);

private:
  SDL_Rect _sourceRect;
  SDL_Texture *_spriteSheet;
  float _x, _y;
};

#endif
