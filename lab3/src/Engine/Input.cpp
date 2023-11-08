#include "Engine.h"

void Engine::input() {

    // Продолжаем реализовывать ввод
    /*if (_kbhit()) {
        char c = _getch();
        switch ((char) c) {
        case 'a':
            break;
        default:
            break;
        }
    }*/

    /*HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);*/
    const short bufferSize = 128;
    INPUT_RECORD irInBuff[bufferSize];

    DWORD cNumRead = 0;
    /*BOOL peekSuccessful = PeekConsoleInput(hStdIn, irInBuff, bufferSize, &cNumRead);*/

    for (DWORD i = 0; i < cNumRead; i++) {
        if (irInBuff[i].EventType == KEY_EVENT) {
            KEY_EVENT_RECORD ker = irInBuff[i].Event.KeyEvent;
            if (ker.bKeyDown) {
                //key pressed
                switch ((char)ker.wVirtualKeyCode) {
                case 'a':
                    player.moveLeft();
                    break;
                case 'd':
                    player.moveRight();
                    break;
                default:
                    break;
                }
                std::cout << (char)ker.wVirtualKeyCode << "pressed";
            }
            else {
                // key released
                switch ((char)ker.wVirtualKeyCode) {
                case 'a':
                    player.stopLeft();
                    break;
                case 'd':
                    player.stopRight();
                    break;
                default:
                    break;
                }
                std::cout << (char)ker.wVirtualKeyCode << "released";
            }
        }
    }

    if (_kbhit()) {
        int c = _getch();
        switch ((char)c) {
        case 'a':
            player.moveLeft();
            break;
        case 'd':
            player.moveRight();
            break;
        case ((char) 32):
            player.jump();
            break;
        case ((char) 27):
            is_open = false;
            break;
        default:
            break;
        }
    }
};

