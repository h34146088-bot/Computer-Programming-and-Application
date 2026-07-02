#include "simple_console.h"
#include <windows.h>

Console::Console() : timeoutMs(-1) {
}

void Console::Initscr() {
}

void Console::Cbreak() {
}

void Console::Timeout(int ms) {
    timeoutMs = ms;
}

void Console::Noecho() {
}

void Console::Keypad(int enabled) {
    (void)enabled;
}

int Console::CursSet(int visibility) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    if(!GetConsoleCursorInfo(hOut, &ci)) {
        return 0;
    }

    ci.bVisible = (visibility != 0);
    SetConsoleCursorInfo(hOut, &ci);
    return 1;
}

int Console::TranslateArrow(int code) {
    switch(code) {
    case 72:
        return KEY_UP;
    case 80:
        return KEY_DOWN;
    case 75:
        return KEY_LEFT;
    case 77:
        return KEY_RIGHT;
    default:
        return code;
    }
}

int Console::Getch() {
    if(timeoutMs < 0) {
        int c = _getch();
        if(c == 0 || c == 0xE0) {
            int c2 = _getch();
            return TranslateArrow(c2);
        }
        return c;
    }

    int waited = 0;
    while(waited < timeoutMs) {
        if(_kbhit()) {
            int c = _getch();
            if(c == 0 || c == 0xE0) {
                int c2 = _getch();
                return TranslateArrow(c2);
            }
            return c;
        }
        Sleep(10);
        waited += 10;
    }

    return ERR;
}

void Console::MvAddCh(int y, int x, int ch) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    DWORD written = 0;
    char out = (char)ch;
    SetConsoleCursorPosition(hOut, pos);
    WriteConsoleA(hOut, &out, 1, &written, NULL);
}

void Console::Endwin() {
    CursSet(1);
}

void Console::GetMaxYX(int &y, int &x) const {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
