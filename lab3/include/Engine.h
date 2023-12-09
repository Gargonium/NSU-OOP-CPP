#pragma once

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
	std::vector<Tile> lvl_border;
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

	std::vector<std::tuple<std::string, std::string, int>> leader_board;

	char* leaderboard_path;
	char* level1_path;
	char* level2_path;
	char* level3_path;
	char* level4_path;
	char* en_mus_path;
	char* bg_mus_path;
	char* walk_mus_path;
	char* menu_mus_path;
	char* death_mus_path;
	char* door_mus_path;

	void readLevel();
	void action(GameContext* ctx);
	void draw();

	void Settings();
	void LeaderBoard();
	void updateLeaderBoard(bool is_new);
public:
	Engine();
	~Engine();
	void start();
	void Menu();
};