#include "Enemy.h"

Enemy::Enemy() {
	last_time_move = now();
	last_time_anim = now();
	is_direction_left = true;
	animation_on = false;
}

void Enemy::action(GameContext* ctx) {
	std::map<char, bool> isObj = findNearObj(ctx);

	if ((now() - last_time_move) / 1ms > 100) {
		if (is_direction_left) {
			if (!isObj['L']) {
				setX(getX() - 1);
			}
			else {
				is_direction_left = false;
			}
		}
		else {
			if (!isObj['R']) {
				setX(getX() + 1);
			}
			else {
				is_direction_left = true;
			}
		}
		last_time_move = now();
	}

	if ((now() - last_time_anim) / 1ms > 200) {
		animation_on ? animation_on = false : animation_on = true;
		last_time_anim = now();
	}
	
	ctx->setEnemiesCoords(id, getY(), getX());
}

void Enemy::draw() {
	if (animation_on) {
		out(getY(), getX(), "-");
	}
	else if (is_direction_left) {
		out(getY(), getX(), "]");
	}
	else {
		out(getY(), getX(), "[");
	}
}

std::map<char, bool> Enemy::findNearObj(GameContext* ctx) {
	std::vector<std::tuple<int, int>> tiles_coords;
	tiles_coords = ctx->getTilesCoords();

	std::tuple<int, int> door_coords;
	door_coords = ctx->getDoorCoords();

	std::map<char, bool> isObj{
		{'R', false}, {'L', false}
	};

	bool findRight = false;
	bool findLeft = false;
	int x, y;

	for (std::tuple<int, int> coords : tiles_coords) {
		std::tie(y, x) = coords;
		if (getY() == y) {
			if (getX() + 1 == x) {
				isObj['R'] = true;
			}
			else if (getX() - 1 == x) {
				isObj['L'] = true;
			}
		}

		if (getY() + 1 == y) {
			if (getX() - 1 == x) {
				findLeft = true;
			}
			else if (getX() + 1 == x) {
				findRight = true;
			}
		}
	}

	if (!findLeft) {
		isObj['L'] = true;
	}
	if (!findRight) {
		isObj['R'] = true;
	}

	std::tie(y, x) = door_coords;
	if (is_direction_left) {
		if (getX() - 1 == x && getY() == y) {
			isObj['L'] = true;
		}
	}
	else {
		if (getX() + 1 == x && getY() == y) {
			isObj['R'] = true;
		}
	}

	return isObj;
}

void Enemy::setId(int ID) {
	id = ID;
}

int Enemy::getId() {
	return id;
}