#include "..\include\Canvas.h"
#include "..\include\Enemy.h"
#include <random>

Enemy::Enemy() {
	en_x = horizontal - 1;
	en_y = (rand() % (vertical - 2)) + 1;
	direction = false;
};

void Enemy::renderEnemy(Canvas& can) {
	can.setChar(en_x, en_y, '@');
};

int Enemy::getX() {
	return en_x;
};

int Enemy::getY() {
	return en_y;
};

void Enemy::movement(Canvas& can) {
	can.setChar(en_x, en_y, field_bg);
	if (direction) {
		en_y--;
		if (en_y == 0) {
			direction = false;
		}
	}
	else {
		en_y++;
		if (en_y == vertical - 1) {
			direction = true;
		}
	}
	renderEnemy(can);
};

void Enemy::shot(Canvas& can) {
	can.setChar(en_x, en_y, field_bg);
	en_x = horizontal - 1;
	en_y = (rand() % (vertical - 2)) + 1;

	renderEnemy(can);
};
