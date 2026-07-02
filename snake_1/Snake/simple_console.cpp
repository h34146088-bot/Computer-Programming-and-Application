#include "simple_console.h"
#include <windows.h>
#include <stdio.h>

WINDOW* stdscr = (WINDOW*)1; // dummy non-null
int timeout_ms = -1; // -1 means block

void initscr() {
    // no-op for console
}

void cbreak() {
    // no-op
}

void timeout(int ms) {
    timeout_ms = ms;
}

void noecho() {
    // using _getch(), so no echo is default
}

void keypad(WINDOW* w, int enabled) {
    (void)w; (void)enabled;
}

int curs_set(int visibility) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    if (!GetConsoleCursorInfo(hOut, &ci)) return 0;
    ci.bVisible = (visibility != 0);
    SetConsoleCursorInfo(hOut, &ci);
    return 1;
}

static int translate_arrow(int code) {
    switch (code) {
    case 72: return KEY_UP;    // up
    case 80: return KEY_DOWN;  // down
    case 75: return KEY_LEFT;  // left
    case 77: return KEY_RIGHT; // right
    default: return code;
    }
}

int simple_getch() {
    if (timeout_ms < 0) {
        int c = _getch();
        if (c == 0 || c == 0xE0) {
            int c2 = _getch();
            return translate_arrow(c2);
        }
        return c;
    }

    int waited = 0;
    while (waited < timeout_ms) {
        if (_kbhit()) {
            int c = _getch();
            if (c == 0 || c == 0xE0) {
                int c2 = _getch();
                return translate_arrow(c2);
            }
            return c;
        }
        Sleep(10);
        waited += 10;
    }
    return ERR; // timeout
}

int getch() {
    return simple_getch();
}

void mvaddch(int y, int x, int ch) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    DWORD written = 0;
    char out = (char)ch;
    SetConsoleCursorPosition(hOut, pos);
    WriteConsoleA(hOut, &out, 1, &written, NULL);
}

void endwin() {
    // Restore cursor visible
    curs_set(1);
}
