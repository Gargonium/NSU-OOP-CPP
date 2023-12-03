#pragma once

#include "GameObject.h"
#include "GameContext.h"

class Enemy : public GameObject {
private:
	int id;
	steady_clock_t last_time_move;
	steady_clock_t last_time_anim;
	bool is_direction_left;
	bool animation_on;
public:
	Enemy();
	void action(GameContext* ctx);
	void draw();

	void setId(int ID);
	int getId();

	std::map<char, bool> findNearObj(GameContext* ctx);
};
