#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>

#include "globals.h"
#include "sprite.h"

class Graphics; // forward declaration

class AnimatedSprite : public Sprite {
public:
  AnimatedSprite();
  AnimatedSprite(Graphics &graphics, const std::string &filePath, int srcX,
                 int srcY, int w, int h, float posX, float posY,
                 float timeToUpdate);

  void playAnimation(std::string name, bool once = false);
  void update(int elapsedTime);
  void draw(Graphics &graphics, int x, int y);
  // virtual void setupAnimations();

private:
  std::map<std::string, std::vector<SDL_Rect>> _animation;
  std::map<std::string, Vector2<int>> _offsets;
};

#endif
