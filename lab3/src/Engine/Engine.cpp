#include "Engine.h"


Engine::Engine() {
    player.setCurMaxXY(0, box.getHeight() - 2 - 2, box.getWidth() - 3, box.getHeight() - 2);
    player.setLevel(box.getLevel(), box.getFloorCount());
    is_open = true;
    delay = 500;

    hStdIn = GetStdHandle(STD_INPUT_HANDLE); 
    
    GetConsoleMode(hStdIn, &prev_mode);
    SetConsoleMode(hStdIn, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleMode(hStdIn, ENABLE_MOUSE_INPUT); 

    ReadConsoleInput(hStdIn, &InputRecord, 1, &Events); 
};

Engine::~Engine() {
    
}

uint64_t Engine::current_timestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

void Engine::start() {

    // Надо понять как правильно использовать время, потому что пока оно нахуй не нужно

    draw();

    uint64_t currentTime = current_timestamp();
    uint64_t fallTime = currentTime + delay;

    std::thread in(input);

    while (is_open) {
        currentTime = current_timestamp();

        if (currentTime > fallTime) {
            fallTime = currentTime + delay;
            player.activateGravity();
        }

        in.join();
        update();
        draw();
    }
};



