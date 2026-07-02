#include "game.h"
#include <stdlib.h>
#include <time.h>

Game::Game() : console(), snake1(NULL), snake2(NULL),
               targetX(0), targetY(0), maxX(0), maxY(0),
               gameEnded(false), gameTerminated(false),
               snake1Dead(false), snake2Dead(false),
               previousSnake1HeadX(0), previousSnake1HeadY(0),
               previousSnake2HeadX(0), previousSnake2HeadY(0) {
    console.Initscr();
    console.Cbreak();
    console.Timeout(300);
    console.Noecho();
    console.Keypad(TRUE);
    console.CursSet(0);
    console.GetMaxYX(maxY, maxX);

    // seed RNG and create snakes at random non-negative positions inside bounds
    srand((unsigned)time(NULL));
    int x1 = rand() % maxX;
    int y1 = rand() % maxY;
    int x2 = rand() % maxX;
    int y2 = rand() % maxY;
    // ensure starting positions are different; if same, shift second
    if(x1 == x2 && y1 == y2) {
        x2 = (x2 + 3) % maxX;
        y2 = (y2 + 2) % maxY;
    }

    snake1 = new Snake(console, x1, y1, Snake::RIGHT, '*');
    snake2 = new Snake(console, x2, y2, Snake::LEFT, '#');

    snake1->SetMapSize(maxX, maxY);
    snake2->SetMapSize(maxX, maxY);

    GenerateNewTarget();
}

Game::~Game() {
    if(snake1)
        delete snake1;
    if(snake2)
        delete snake2;
    console.Endwin();
}

void Game::GenerateNewTarget() {
    targetX = rand() % maxX;
    targetY = rand() % maxY;
    console.MvAddCh(targetY, targetX, '$');
}

void Game::HandleInput() {
    int c = console.Getch();
    switch(c) {
    case KEY_UP:
        snake1->SetDir(Snake::UP);
        break;
    case KEY_DOWN:
        snake1->SetDir(Snake::DOWN);
        break;
    case KEY_LEFT:
        snake1->SetDir(Snake::LEFT);
        break;
    case KEY_RIGHT:
        snake1->SetDir(Snake::RIGHT);
        break;
    case 'W':
    case 'w':
        snake2->SetDir(Snake::UP);
        break;
    case 'S':
    case 's':
        snake2->SetDir(Snake::DOWN);
        break;
    case 'A':
    case 'a':
        snake2->SetDir(Snake::LEFT);
        break;
    case 'D':
    case 'd':
        snake2->SetDir(Snake::RIGHT);
        break;
    case 27:
    case 'q':
        gameTerminated = true;
        break;
    default:
        break;
    }
}

void Game::UpdateGame() {
    previousSnake1HeadX = snake1->GetHeadX();
    previousSnake1HeadY = snake1->GetHeadY();
    previousSnake2HeadX = snake2->GetHeadX();
    previousSnake2HeadY = snake2->GetHeadY();

    snake1Dead = !snake1->MoveSnake();
    snake2Dead = !snake2->MoveSnake();

    if(!snake1Dead && snake1->AtTarget(targetX, targetY)) {
        snake1->Grow();
        GenerateNewTarget();
    }

    if(!snake2Dead && snake2->AtTarget(targetX, targetY)) {
        snake2->Grow();
        GenerateNewTarget();
    }

    CheckCollisions();
}

void Game::CheckCollisions() {
    if(!snake1Dead && !snake2Dead) {
        if(snake1->GetHeadX() == snake2->GetHeadX() && snake1->GetHeadY() == snake2->GetHeadY()) {
            snake1Dead = true;
            snake2Dead = true;
        }

        if(snake1->GetHeadX() == previousSnake2HeadX &&
           snake1->GetHeadY() == previousSnake2HeadY &&
           snake2->GetHeadX() == previousSnake1HeadX &&
           snake2->GetHeadY() == previousSnake1HeadY) {
            snake1Dead = true;
            snake2Dead = true;
        }
    }

    // Check if snakes hit each other's body
    if(!snake1Dead && !snake2Dead) {
        if(snake2->HitBody(snake1->GetHeadX(), snake1->GetHeadY())) {
            snake1Dead = true;
        }
        if(snake1->HitBody(snake2->GetHeadX(), snake2->GetHeadY())) {
            snake2Dead = true;
        }
    }

    if(snake1Dead || snake2Dead || gameTerminated) {
        gameEnded = true;
    }
}

void Game::Run() {
    while(!gameEnded) {
        HandleInput();
        UpdateGame();
    }
}
