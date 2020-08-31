#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <chrono>
#include <future>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

// Game class store game state and runs game loop to update game state
class Game {
public:
  Game(const std::size_t &grid_width,
       const std::size_t &grid_height); // constructor

  void Run(Controller const &controller, Renderer &renderer,
           const std::size_t &target_frame_duration); // start the game and update game state
  int GetScore() const;
  int GetSize() const;
  int difficulity_level{0}; 

private:
  Snake snake;    // Snake class obj in Game class
  SDL_Point food; // a struct have int x, y coords
  std::mutex game_mutex;

  // generate random number to place food
  std::random_device dev; // random number generator
  std::mt19937 engine;    // pseudo random number generator
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  void PlaceFood();
  void Update();
};

#endif