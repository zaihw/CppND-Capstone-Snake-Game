#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <deque>

// Snake class defines the snake object which will be used(updated) in the game 
class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(const int &grid_width, const int &grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  //void setPosition(float x, float y){ head_x = x; head_y = y; }

  Direction direction = Direction::kUp;
  std::deque<SDL_Point> body; // store body points in deque
  float speed{0.1f};
  int size{1};
  bool alive{true};
  bool moved{false};
  float head_x;
  float head_y;
  static std::vector<std::vector<bool>> grid;

  void Update();
  void GrowBody();
  bool SnakeCell(const int &x, const int &y);
  bool GetFood(SDL_Point food);

 private:
  int score{0};
  bool growing{false};
  int grid_width;
  int grid_height;

  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
};

#endif