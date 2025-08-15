#include "input.h"

/**
 * Handles input stuff
 */
void Input::beginNewFrame() {
  this->_pressedKeys.clear();
  this->_releasedKeys.clear();
}

void Input::keyUp(const SDL_Event &event) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "key released: %d", event.key.keysym.scancode);
  this->_releasedKeys[event.key.keysym.scancode] = true;
  this->_heldKeys[event.key.keysym.scancode] = false;
}

void Input::keyDown(const SDL_Event &event) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "key pressed: %d", event.key.keysym.scancode);
  this->_pressedKeys[event.key.keysym.scancode] = true;
  this->_heldKeys[event.key.keysym.scancode] = true;
}

bool Input::wasKeyPressed(SDL_Scancode key) { return this->_pressedKeys[key]; }

bool Input::wasKeyReleased(SDL_Scancode key) {
  return this->_releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key) { return this->_heldKeys[key]; }
