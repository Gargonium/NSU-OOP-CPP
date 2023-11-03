#include "Canvas.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <iostream>

Bullet::Bullet(Player& pl) {
	bul_x = pl.getXCoordinate() + 1;
	bul_y = pl.getYCoordinate();
};

Bullet::~Bullet() {
};

void Bullet::renderBullet(Canvas& can) {
	can.setChar(bul_x, bul_y, 'o');
	can.renderCanvas();
};

void Bullet::setBulletCoordinates(Player& pl) {
	bul_x = pl.getXCoordinate() + 1;
	bul_y = pl.getYCoordinate();
};

bool Bullet::bulletFly(Player& pl, Canvas& can, Enemy& en) {
	can.setChar(bul_x, bul_y, field_bg);
	bul_x++;
	renderBullet(can);

	if ((bul_x == en.getX()) && (bul_y == en.getY())) {
		can.incScore();
		en.shot(can);
	}

	if (bul_x == horizontal - 1) {
		can.setChar(bul_x, bul_y, field_bg);
		setBulletCoordinates(pl);
		can.renderCanvas();
		return false;
	}
	return true;
};
