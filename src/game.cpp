#include "game.h"
#include "SDL.h"
#include <iostream>

std::mutex mutlock;

Game::Game(const std::size_t &grid_width, const std::size_t &grid_height)
    : snake(grid_width, grid_height),
      engine(dev()), // engine use a pseudo random number as seed, make sure
      // each constructor call, engine will have a different initial state
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               const std::size_t &target_frame_duration) {
  Uint32 title_timestamp =
      SDL_GetTicks(); // title is also updating, get a timestamp for .this title
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::cout << "Game Starting...!\n";
  while (running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    frame_start = SDL_GetTicks(); // timestamp start of frame

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks(); // timestamp end of frame

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(GetScore(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceFood() {
  int x, y;
  while (true) {
    // engine initial state is different in each Game constructor call
    // so food placement will be different in each game
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive)
    return;

  snake.Update();

  // int new_x = static_cast<int>(snake.head_x);
  // int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == static_cast<int>(snake.head_x) &&
      food.y == static_cast<int>(snake.head_y)) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.025;
  }
}
