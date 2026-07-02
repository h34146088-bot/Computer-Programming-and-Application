// Minimal replacement for curses functions used by this program.
#pragma once

#include <conio.h>
#include <windows.h>

#ifndef ERR
#define ERR (-1)
#endif
#ifndef OK
#define OK 0
#endif

#define KEY_UP 1000
#define KEY_DOWN 1001
#define KEY_LEFT 1002
#define KEY_RIGHT 1003

class Console {
  public:
    Console();
    void Initscr();
    void Cbreak();
    void Timeout(int ms);
    void Noecho();
    void Keypad(int enabled);
    int CursSet(int visibility);
    int Getch();
    void MvAddCh(int y, int x, int ch);
    void Endwin();
    void GetMaxYX(int &y, int &x) const;

  private:
    int timeoutMs;
    static int TranslateArrow(int code);
};
