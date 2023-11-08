#include "Player.h"

Player::Player() {
	m_x = 0;
	m_y = 0;

	m_max_x = 0;
	m_max_y = 0;

	is_coor_updated = false;
	m_left_pressed = false;
	m_right_pressed = false;
	m_gravity = false;
	is_in_air = false;

	m_player_sym = 'S';

	m_speed = 5;

	m_changes.changes = new CHANGE[10];
	m_changes.changes_count = 0;

	glv::makeChange(m_changes, m_x, m_y, m_player_sym);

	level = nullptr;
	floor_count = 0;
}

Player::~Player() {
	delete[] m_changes.changes;
}

void Player::setCurMaxXY(int x, int y, int max_x, int max_y) {
	m_x = x;
	m_y = y;

	m_max_x = max_x;
	m_max_y = max_y;

	is_coor_updated = true;
}

void Player::moveRight() {
	m_right_pressed = true;
}

void Player::moveLeft() {
	m_left_pressed = true;
}

void Player::stopRight() {
	m_right_pressed = false;
}

void Player::stopLeft() {
	m_left_pressed = false;
}

void Player::activateGravity() {
	m_gravity = true;
}

void Player::deactivateGravity() {
	m_gravity = false;
}

void Player::jump() {
	if (!is_in_air) {
		m_y -= 2;
		is_in_air = true;
		is_coor_updated = true;
		if (m_y < 0) {
			m_y = 0;
		}
	}
}

void Player::setLevel(Floor* lvl, int fl_count) {
	floor_count = fl_count;
	level = lvl;
}

bool Player::isFloor(int x, int y) {
	for (int i = 0; i < floor_count; i++) {
		if (level[i].getX() == x) {
			if (level[i].getY() == y) {
				return true;
			}
		}
	}
	return false;
}

bool Player:: isCollision(char direction) {

	switch (direction) {
	case 'r':
		if ((m_x > m_max_x) || isFloor(m_x + 1, m_y)) {
			return true;
		}
		break;
	case 'l':
		if ((m_x <= 0) || isFloor(m_x - 1, m_y)) {
			return true;
		}
		break;
	case 'u':
		if ((m_y < 0) || isFloor(m_x, m_y - 1)) {
			return true;
		}
		break;
	case 'd':
		if ((m_y >= m_max_y) || isFloor(m_x, m_y + 1)) {
			is_in_air = false;
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}