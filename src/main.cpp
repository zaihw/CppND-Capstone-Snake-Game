#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "SDL2/SDL.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string difficulity;

  SDL_Init(SDL_INIT_VIDEO);

  std::cout << "Choose level of difficulity by type below options:" << std::endl;
  std::cout << "easy, medium, hard" << std::endl;
  std::cout << "do not include the comma or space" << std::endl;
  std::cout << "Type in your choice: " << std::endl;
  std::getline(std::cin, difficulity);
  //std::cin >> difficulity;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  if (difficulity == "easy"){
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  } else {
    std::cout << "pay attention to the instruction when selecting difficulity" << std::endl;
  }

  // run game until game is ended or terminated
  game.Run(controller, renderer, kMsPerFrame);
  
  std::cout << "Game Over!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  return 0;
}