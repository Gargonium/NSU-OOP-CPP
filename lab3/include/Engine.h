#pragma once

#include <curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>

#include <curses.h>
#include <stdio.h>

#include "GameContext.h"
#include "Tile.h"
#include "Player.h"
#include "Door.h"
#include "Enemy.h"

#define ESC_CODE 27

class Engine {
private:
	GameContext ctx;
	std::vector<Tile> level;
	std::vector<Enemy> enemies;
	Player player;
	Door door;

	int lvl_num;
	int lvl_count;
public:
	Engine();
	~Engine();
	void start();
	void readLevel();
	void allAction(GameContext* ctx);
	void allDraw();
};