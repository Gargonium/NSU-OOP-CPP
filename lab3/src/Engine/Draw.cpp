#include "Engine.h"
#include "Player.h"
#include "Box.h"

void Engine::draw() {

    player.drawPlayer();

    box.drawBox();

};

void Player::drawPlayer() {
    glv::drawChanges(m_changes);
}

void Box::drawBox() {
    glv::drawChanges(m_changes);
}
