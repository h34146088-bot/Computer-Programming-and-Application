// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "simple_console.h"
#include "snake.h"
#include <iostream>

using namespace std;
extern int maxX;
extern int maxY;

int main() {
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

    Snake *snake = NewSnake(1, 1, RIGHT);
    GenerateNewTarget(snake);

    while(!gameEnded) {
        c = getch();
        switch(c) {
        case KEY_UP:
            SetDir(snake, UP);
            break;
        case KEY_DOWN:
            SetDir(snake, DOWN);
            break;
        case KEY_LEFT:
            SetDir(snake, LEFT);
            break;
        case KEY_RIGHT:
            SetDir(snake, RIGHT);
            break;
        case 27:
        case 'q':
            gameTerminated = true;
            break;
        default:
            break;
        }

        gameEnded = !MoveSnake(snake) || gameTerminated;
    }
    DeleteSnake(snake);
    endwin(); // Restores the terminal after Curses activity
}
