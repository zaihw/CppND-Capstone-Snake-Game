#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

// Controller class to handle user inputs to change snake direction
class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif