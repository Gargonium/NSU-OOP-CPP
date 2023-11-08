#include "Engine.h"
#include "Player.h"
#include "Box.h"

void Engine::update() {

    player.updatePlayer();

    box.updateBox();

};

void Player::updatePlayer() {

    if (m_left_pressed != m_right_pressed) {
        if (m_left_pressed) {
            if (!isCollision('l')) {
                m_x--;
                is_coor_updated = true;
            }
            stopLeft();
        }
        else {
            if (m_right_pressed) {
                if (!isCollision('r')) {
                    m_x++;
                    is_coor_updated = true;
                }
                stopRight();
            }
        }
    }

    if (m_gravity) {
        if (!isCollision('d')) {
            m_y++;
            is_coor_updated = true;
        }
        deactivateGravity();
    }


    if (is_coor_updated) {
        glv::makeChange(m_changes, m_x, m_y, m_player_sym);
        is_coor_updated = false;
    }
}

void Box::updateBox() {
  
}