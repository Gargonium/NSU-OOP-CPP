#pragma once

#include <vector>
#include <tuple>

class GameContext {
private:
	char input;
	bool game_over;
	bool next_lvl;

	std::tuple<int, int> player_coords;
	std::tuple<int, int> door_coords;
	std::vector<std::tuple<int, int>> enemies_coords;
	std::vector<std::tuple<int, int>> tiles_coords;

	int console_height;
	int console_width;

	char* en_mus_path;
	char* walk_mus_path;
	char* door_mus_path;
	char* death_mus_path;

	bool is_music_on;

	int difficulty;

public:
	GameContext();
	
	void setInput(char c);
	char getInput();

	void setPlayerCoords(int y, int x);
	void setDoorCoords(int y, int x);
	void setEnemiesCoords(int id, int y, int x);
	void setEnemiesCoords(std::vector<std::tuple<int, int>> coords);
	void setTilesCoords(std::vector<std::tuple<int, int>> coords);

	std::tuple<int, int> getPlayerCoords();
	std::tuple<int, int> getDoorCoords();
	std::vector<std::tuple<int, int>> getEnemiesCoords();
	std::vector<std::tuple<int, int>> getTilesCoords();

	void clear();

	void NextLvl(bool is_true);
	void GameOver(bool is_true);
	bool isNextLvl();
	bool isGameOver();

	void setConsoleDimensions(int height, int width);
	int getConsoleHeight();
	int getConsoleWidth();

	void setMusicPaths(char* enemy, char* walk, char* death, char* door);
	char* getEnemyMusic();
	char* getWalkMusic();
	char* getDeathMusic();
	char* getDoorMusic();

	void setMusicStatus(bool is_true);
	bool getMusicStatus();

	void setDifficulty(int diff);
	int getDifficulty();
};