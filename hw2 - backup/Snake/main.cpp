// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "simple_console.h"
#include "snake.h"
#include <iostream>

using namespace std;

int main() {
    int maxX;
    int maxY;
    int c;
    bool gameEnded = false;
    bool gameTerminated = false;

    initscr();
    cbreak();                     // Disable buffering, making input available to the program immediately
    timeout(500);                 // Wait user's input for at most 1s
    noecho();                     // Turn off the echos of key strokes
    keypad(stdscr, TRUE);         // Enable input from arrow keys
    curs_set(0);                  // Hide cursor
    getmaxyx(stdscr, maxY, maxX); // Get max X and Y of the terminal

    Snake snake1(1, 1, Snake::RIGHT);
    Snake snake2(10, 10, Snake::LEFT);
    snake1.SetMapSize(maxX, maxY);
    snake2.SetMapSize(maxX, maxY);
    snake1.GenerateNewTarget();

    while(!gameEnded) {
        c = getch();
        switch(c) {
        case KEY_UP:
            snake1.SetDir(Snake::UP);
            break;
        case KEY_DOWN:
            snake1.SetDir(Snake::DOWN);
            break;
        case KEY_LEFT:
            snake1.SetDir(Snake::LEFT);
            break;
        case KEY_RIGHT:
            snake1.SetDir(Snake::RIGHT);
            break;
        case 'W':
        case 'w':
            snake2.SetDir(Snake::UP);
            break;
        case 'S':
        case 's':
            snake2.SetDir(Snake::DOWN);
            break;
        case 'A':
        case 'a':
            snake2.SetDir(Snake::LEFT);
            break;
        case 'D':
        case 'd':
            snake2.SetDir(Snake::RIGHT);
            break;
        case 27:
        case 'q':
            gameTerminated = true;
            break;
        default:
            break;
        }
        bool snake1Dead = !snake1.MoveSnake();
        bool snake2Dead = !snake2.MoveSnake();

        bool snake1Hit = false;
        bool snake2Hit = false;

        if(!snake1Dead && !snake2Dead) {
            snake1Hit =
                snake2.HitBody(
                    snake1.GetHeadX(),
                    snake1.GetHeadY());

            snake2Hit =
                snake1.HitBody(
                    snake2.GetHeadX(),
                    snake2.GetHeadY());
        }

        gameEnded = 
            snake1Dead ||
            snake2Dead ||
            snake1Hit ||
            snake2Hit ||
            gameTerminated;
    }
    endwin(); // Restores the terminal after Curses activity
}
