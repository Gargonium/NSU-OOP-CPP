#include "Player.h"
#include "Canvas.h"


Player::Player(int diff) {
	pl_x = 0;
	pl_y = 0;
	difficulty = diff;
};

Player::Player() {
	pl_x = 0;
	pl_y = 0;
	difficulty = 1;
};


int Player::getXCoordinate() {
	return pl_x;
};

int Player::getYCoordinate() {
	return pl_y;
};

void Player::renderPlayer(Canvas& can) {
	can.setChar(pl_x, pl_y, '$');
	can.renderCanvas();
};

void Player::clearPlayer(Canvas& can) {
	can.setChar(pl_x, pl_y, field_bg);
};

void Player::moveLeft(Canvas& can) {
	if (pl_x != 0) {
		clearPlayer(can);
		this->pl_x--;
		renderPlayer(can);
	}
};

void Player::moveRight(Canvas& can) {
	if (pl_x != difficulty) {
		clearPlayer(can);
		this->pl_x++;
		renderPlayer(can);
	}
};

void Player::moveUp(Canvas& can) {
	if (pl_y != 0) {
		clearPlayer(can);
		this->pl_y--;
		renderPlayer(can);
	}
};

void Player::moveDown(Canvas& can) {
	if (pl_y != vertical - 1) {
		clearPlayer(can);
		this->pl_y++;
		renderPlayer(can);
	}
};
