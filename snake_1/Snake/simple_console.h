// Minimal replacement for curses functions used by this program.
#pragma once

#include <windows.h>
#include <conio.h>

typedef struct _win WINDOW;
extern WINDOW* stdscr;
extern int timeout_ms;

#ifndef ERR
#define ERR (-1)
#endif
#ifndef OK
#define OK 0
#endif

#define KEY_UP    1000
#define KEY_DOWN  1001
#define KEY_LEFT  1002
#define KEY_RIGHT 1003

void initscr();
void cbreak();
void timeout(int ms);
void noecho();
void keypad(WINDOW* w, int enabled);
int curs_set(int visibility);
int simple_getch();
int getch();
void mvaddch(int y, int x, int ch);
void endwin();

/* Macro compatible with usage: getmaxyx(stdscr, maxY, maxX); */
#define getmaxyx(win,y,x) \
    do { \
        CONSOLE_SCREEN_BUFFER_INFO csbi; \
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); \
        (y) = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; \
        (x) = csbi.srWindow.Right - csbi.srWindow.Left + 1; \
    } while(0)
