#pragma once

#include <curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>

#include <curses.h>
#include <stdio.h>

#include "GameObject.h"
#include "GameContext.h"
#include "Tile.h"
#include "Player.h"
#include "Door.h"
#include "Enemy.h"

#define _WIN32_WINNT 0x0500
#include <windows.h>

const int ESC_CODE = 27;

class Engine : public GameObject {
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

	bool game_on;

	int difficulty;
	bool is_music_on;

	int time_score;
	steady_clock_t game_launch_time;

	std::string nickname;

	void readLevel();
	void action(GameContext* ctx);
	void draw();

	void Menu();
	void Settings();
	void LeaderBoard();
public:
	Engine();
	~Engine();
	void start();
};