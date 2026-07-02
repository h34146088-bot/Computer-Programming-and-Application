#ifndef GAME_H
#define GAME_H

#include "simple_console.h"
#include "snake.h"

class Game {
  public:
    Game();
    ~Game();
    void Run();

  private:
    Console console;
    Snake *snake1;
    Snake *snake2;
    int targetX;
    int targetY;
    int maxX;
    int maxY;
    bool gameEnded;
    bool gameTerminated;
    bool snake1Dead;
    bool snake2Dead;
    int previousSnake1HeadX;
    int previousSnake1HeadY;
    int previousSnake2HeadX;
    int previousSnake2HeadY;

    void GenerateNewTarget();
    void HandleInput();
    void UpdateGame();
    void CheckCollisions();
};

#endif
