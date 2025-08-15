#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float SPRITE_SCALE = 0.5f;
} // namespace globals

template <typename T> struct Vector2 {
  T x, y;
  Vector2() : x(0), y(0) {}
  Vector2(T x, T y) : x(x), y(y) {}

  Vector2 zero() { return Vector2(0, 0); }
};

#endif
