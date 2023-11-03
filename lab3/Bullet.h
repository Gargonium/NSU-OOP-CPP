#pragma once

#include "Player.h"
#include "Enemy.h"

class Bullet : public Player {
private:
	int bul_x;
	int bul_y;
public:
	Bullet(Player& pl);

	~Bullet();

	void renderBullet(Canvas& can);

	void setBulletCoordinates(Player& pl);

	bool bulletFly(Player& pl, Canvas& can, Enemy& en);
};
