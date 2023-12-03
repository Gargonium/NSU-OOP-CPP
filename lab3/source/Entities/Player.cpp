#include "Player.h"

Player::Player() {
	lives = 3;
	last_time_move = now();
	is_in_air = false;
}

void Player::action(GameContext* ctx) {
	
	std::map<char, bool> isObj = findNearObj(ctx);

	if (isObj['Q']) {
		ctx->NextLvl(true);
	}

	if (isObj['E']) {
		lives--;
		setX(start_x);
		setY(start_y);
		if (lives == 0) {
			ctx->GameOver();
		}
	}

	switch (ctx->getInput()) {
	case 'a':
		if (!isObj['L']) {
			setX(getX() - 1);
		}
		break;
	case 'd':
		if (!isObj['R']) {
			setX(getX() + 1);
		}
		break;
	case ' ':
		if (!is_in_air && !isObj['u']) {
			if (isObj['U']) {
				setY(getY() - 1);
			}
			else {
				setY(getY() - 2);
			}
			last_time_move = now();
			is_in_air = true;
		}
		break;
	default: break;
	}

	if ((now() - last_time_move) / 1ms > 200) {
		if (!isObj['D']) {
			setY(getY() + 1);
			last_time_move = now();
		}
		else {
			is_in_air = false;
		}
	}

	ctx->setPlayerCoords(getY(), getX());
}

void Player::draw() {
	out(getY(), getX(), "P");
	out(1, 1, "Lives: %d", lives);
}

void Player::setStartXY(int n_y, int n_x) {
	start_x = n_x;
	start_y = n_y;
}

std::map<char, bool> Player::findNearObj(GameContext* ctx) {
	std::vector<std::tuple<int, int>> tiles_coords;
	tiles_coords = ctx->getTilesCoords();

	std::vector<std::tuple<int, int>> enemies_coords;
	enemies_coords = ctx->getEnemiesCoords();

	std::tuple<int, int> door_coords;
	door_coords = ctx->getDoorCoords();

	std::map<char, bool> isObj{
		{'U', false}, {'u', false}, {'D', false}, {'R', false}, {'L', false}, {'Q', false}, {'E', false}
	};

	int x, y;

	for (std::tuple<int, int> coords : tiles_coords) {
		std::tie(y, x) = coords;
		if (getX() == x) {
			if (getY() + 1 == y) {
				isObj['D'] = true;
			}
			else if (getY() - 1 == y) {
				isObj['u'] = true;
			}
			else if (getY() - 2 == y) {
				isObj['U'] = true;
			}
		}
		if (getY() == y) {
			if (getX() + 1 == x) {
				isObj['R'] = true;
			}
			else if (getX() - 1 == x) {
				isObj['L'] = true;
			}
		}
	}

	for (std::tuple<int, int> coords : enemies_coords) {
		std::tie(y, x) = coords;
		if (getX() == x && getY() == y) {
			isObj['E'] = true;
		}
	}

	std::tie(y, x) = door_coords;
	if (getX() == x && getY() == y) {
		isObj['Q'] = true; // Q - quit
	}

	return isObj;
}