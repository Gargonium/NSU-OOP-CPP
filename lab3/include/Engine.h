#pragma once

#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Globals.h"
#include "Player.h"
#include "Box.h"

#include <conio.h>

class Engine:public Player, public Box{
private:

	void input();

	void update();

	void draw();

	Box box;

	Player player;

	bool is_open;

	int delay;

	uint64_t current_timestamp();

public:
	Engine();

	~Engine();

	void start();
};
