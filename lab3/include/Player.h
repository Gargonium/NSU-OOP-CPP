#pragma once

#include "GameObject.h"

class Player : public GameObject {
private:
	int lives;
	int start_x;
	int start_y;
	steady_clock_t last_time_move;
	bool is_in_air;

	std::map<char, bool> findNearObj(GameContext* ctx);
	void death(GameContext* ctx);
public:
	Player();
	void action(GameContext* ctx);
	void draw();
	void setStartXY(int n_y, int n_x);
	void setLives(int l);
};