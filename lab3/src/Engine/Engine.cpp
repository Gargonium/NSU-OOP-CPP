#include "Engine.h"


Engine::Engine() {
    player.setCurMaxXY(0, box.getHeight() - 2 - 2, box.getWidth() - 3, box.getHeight() - 2);
    player.setLevel(box.getLevel(), box.getFloorCount());
    is_open = true;
    delay = 500;
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

    while (is_open) {
        currentTime = current_timestamp();

        if (currentTime > fallTime) {
            fallTime = currentTime + delay;
            player.activateGravity();
        }

        input();
        update();
        draw();
    }
};



