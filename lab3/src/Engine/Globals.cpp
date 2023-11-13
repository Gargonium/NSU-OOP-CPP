#include "Globals.h"

void glv::drawChanges(CHANGES& ch) {
    if (ch.changes_count != 0) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout << "\b "; 
        for (int i = 0; i < ch.changes_count; i++) {
            SetConsoleCursorPosition(hStdOut, ch.changes[i].coord);
            std::cout << ch.changes[i].symbol;
        }
        ch.changes_count = 0;
    }
}

void glv::drawChanges(CHANGES& ch, int old_x, int old_y) {
    if (ch.changes_count != 0) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        
        SetConsoleCursorPosition(hStdOut, makeCoord(old_x, old_y));
        std::cout << "\b ";

        for (int i = 0; i < ch.changes_count; i++) {
            SetConsoleCursorPosition(hStdOut, ch.changes[i].coord);
            std::cout << ch.changes[i].symbol;
        }
        ch.changes_count = 0;
    }
}

COORD glv::makeCoord(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    return coord;
};

void glv::makeChange(CHANGES& ch, int x, int y, char c) {
    ch.changes[ch.changes_count].coord = makeCoord(x, y);
    ch.changes[ch.changes_count].symbol = c;
    ch.changes_count++;
}

