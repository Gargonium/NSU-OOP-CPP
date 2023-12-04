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

#define _WIN32_WINNT 0x0500
#include <windows.h>

#define ESC_CODE 27 // лучше const

class Engine {
private:
	GameContext ctx;
	std::vector<Tile> level;
	std::vector<Enemy> enemies;
	Player player;
	Door door;

	int lvl_num;
	int lvl_count;

	int console_height;
	int console_width;

	void readLevel();
	void allAction(GameContext* ctx);
	void allDraw();
public:
	Engine();
	~Engine();
	void start();
};