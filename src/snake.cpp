#include "snake.h"
#include "game.h"
#include <cmath>
#include <iostream>
#include <thread>

// extern std::mutex mutlock;

// compare head position current_cell with prev_cell position
// if moved, call UpdateBody()
void Snake::Update() {
  SDL_Point prev_cell{static_cast<int>(head_x), static_cast<int>(head_y)};
  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{static_cast<int>(head_x), static_cast<int>(head_y)};
  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::GrowBody() { growing = true; }

// method to check if cell is occupied by snake before place food.
bool Snake::SnakeCell(const int &x, const int &y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

// Check if eat food, if yes, increase score, grow body
bool Snake::GetFood(SDL_Point food) {
  bool got_food = false;
  int new_x = static_cast<int>(head_x);
  int new_y = static_cast<int>(head_y);

  if (food.x == new_x && food.y == new_y) {
    got_food = true;
    score++;
    GrowBody();
  }

  return got_food;
}

// update head_x head_y value y direction and speed then fmod
void Snake::UpdateHead() {
  // origin at top left corner
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

// make previous head position part of body
// if got food and not growing, remove tail
// if growing, keep tail
void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}