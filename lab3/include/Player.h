#pragma once

#include "Globals.h"
#include "Box.h"

class Player {
private:

	CHANGES m_changes;

	Floor* level;
	int floor_count;

	int m_x;
	int m_y;

	int m_max_x;
	int m_max_y;

	int m_speed;

	char m_player_sym;

	bool is_coor_updated;
	bool m_left_pressed;
	bool m_right_pressed;
	bool m_gravity;
	bool is_in_air;

public:
	Player();

	virtual ~Player();

	void updatePlayer();

	void drawPlayer();

	void setCurMaxXY(int x, int y, int max_x, int max_y);

	void moveRight();

	void moveLeft();

	void stopRight();

	void stopLeft();

	void activateGravity();

	void deactivateGravity();

	void jump();

	bool isCollision(char direction);

	void setLevel(Floor* level, int floor_count);

	bool isFloor(int x, int y);

};
