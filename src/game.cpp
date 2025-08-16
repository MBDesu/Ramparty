#include "game.h"
#include "SDL_log.h"
#include "globals.h"
#include "graphics.h"
#include "input.h"

#include <SDL.h>
#include <algorithm>
#include <iostream>

namespace {
const int FPS_LIMIT = 60;
const int MAX_FRAME_TIME = 6000 / FPS_LIMIT;
} // namespace

/**
 * Handles game loop, etc.
 */
Game::Game() {
  std::cout << "Initializing SDL..." << std::endl;
  int rendererFlags, windowFlags;
  rendererFlags = SDL_RENDERER_ACCELERATED;
  windowFlags = 0;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }
  std::cout << "SDL initialized" << std::endl;
  this->gameLoop();
}

Game::~Game() {}

void Game::gameLoop() {
  Graphics graphics;
  Input input;
  SDL_Event event;

  this->_player =
      Sprite(graphics, "assets/img/player.png", 0, 0, 256, 256, 100, 100);

  int lastUpdateTime = SDL_GetTicks();

  // the game loop
  while (true) {
    input.beginNewFrame();

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        input.keyDown(event);
      } else if (event.type == SDL_KEYUP) {
        input.keyUp(event);
      } else if (event.type == SDL_QUIT) {
        return;
      }
    }

    if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
      return;
    }

    if (input.isKeyHeld(SDL_SCANCODE_UP)) {
      Vector2<float *> currentPosition = this->_player.getPosition();
      *(currentPosition.y) -= globals::CURSOR_SPEED;
      *currentPosition.y =
          std::clamp((int)*currentPosition.y, 0,
                     globals::SCREEN_HEIGHT - this->_player.getHeight());
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "(%.0f, %.0f)",
                  *currentPosition.x, *currentPosition.y);
    }

    if (input.isKeyHeld(SDL_SCANCODE_DOWN)) {
      Vector2<float *> currentPosition = this->_player.getPosition();
      *(currentPosition.y) += globals::CURSOR_SPEED;
      *currentPosition.y =
          std::clamp((int)*currentPosition.y, 0,
                     globals::SCREEN_HEIGHT - this->_player.getHeight());
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "(%.0f, %.0f)",
                  *currentPosition.x, *currentPosition.y);
    }

    if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
      Vector2<float *> currentPosition = this->_player.getPosition();
      *(currentPosition.x) -= globals::CURSOR_SPEED;
      *currentPosition.x =
          std::clamp((int)*currentPosition.x, 0,
                     globals::SCREEN_WIDTH - this->_player.getWidth());
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "(%.0f, %.0f)",
                  *currentPosition.x, *currentPosition.y);
    }

    if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
      Vector2<float *> currentPosition = this->_player.getPosition();
      *(currentPosition.x) += globals::CURSOR_SPEED;
      *currentPosition.x =
          std::clamp((int)*currentPosition.x, 0,
                     globals::SCREEN_WIDTH - this->_player.getWidth());
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "(%.0f, %.0f)",
                  *currentPosition.x, *currentPosition.y);
    }

    const int CURRENT_TIME_MS = SDL_GetTicks();
    const int ELAPSED_TIME_MS = CURRENT_TIME_MS - lastUpdateTime;
    this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
    lastUpdateTime = CURRENT_TIME_MS;

    this->draw(graphics);
    SDL_Delay(16);
  }
}

void Game::draw(Graphics &graphics) {
  graphics.clear();
  this->_player.draw(graphics, *this->_player.getPosition().x,
                     *this->_player.getPosition().y);
  graphics.flip();
}

void Game::update(float elapsedTime) {}
