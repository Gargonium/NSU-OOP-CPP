#include "Engine.h"

void Engine::input() {
    switch (InputRecord.EventType) {
    case KEY_EVENT:
        KeyEventProc(InputRecord.Event.KeyEvent);
        break;

    case MOUSE_EVENT:
        if (InputRecord.Event.MouseEvent.dwEventFlags != MOUSE_MOVED) {
            MouseEventProc(InputRecord.Event.MouseEvent);
        }
        break;

    case WINDOW_BUFFER_SIZE_EVENT:
        ResizeEventProc(InputRecord.Event.WindowBufferSizeEvent);
        break;

    default:
        break;
    }
}

void Engine::MouseEventProc(MOUSE_EVENT_RECORD mer) {
    COORD coord;

    switch (mer.dwEventFlags) {
    case 0:
        if (mer.dwButtonState == MOUSE_WHEELED) {
            coord.X = mer.dwMousePosition.X;
            coord.Y = mer.dwMousePosition.Y;
            //std::cout << "Mouse wheel pressed: X = " << coord.X << ", Y = " << coord.Y << std::endl;
        }
        else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
            coord.X = mer.dwMousePosition.X;
            coord.Y = mer.dwMousePosition.Y;
            //std::cout << "Right mouse button pressed: X = " << coord.X << ", Y = " << coord.Y << std::endl;
        }
        else if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            coord.X = mer.dwMousePosition.X;
            coord.Y = mer.dwMousePosition.Y;
            //std::cout << "Left mouse button pressed: X = " << coord.X << ", Y = " << coord.Y << std::endl;
        }
        break;
    case DOUBLE_CLICK:
        //std::cout << "Double click" << std::endl;
        break;
    case MOUSE_WHEELED:
        //std::cout << "Vertical mouse wheel" << std::endl;
        break;
    default:
        break;
    }
}

void Engine::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr) {
    wbsr.dwSize.X = 0;
    // std::cout << "Console screen buffer is " << wbsr.dwSize.X << " columns by " << wbsr.dwSize.Y << "rows." << std::endl;
}

void Engine::KeyEventProc(KEY_EVENT_RECORD ker) {
    if (ker.bKeyDown) {
        //std::cout << "Key " << ker.wVirtualKeyCode << " pressed" << std::endl;

        switch ((char) ker.wVirtualKeyCode) {
        case 'a':
            player.moveLeft();
            break;
        case 'd':
            player.moveRight();
            break;
        case ' ':
            player.jump();
            break;
        case ((char) 27):
            is_open = false;
        default:
            break;
        }
    }
    else {
        //std::cout << "Key " << ker.wVirtualKeyCode << " released" << std::endl;
    }
}
