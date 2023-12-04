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

	void NextLvl(bool b);
	void GameOver();
	bool isNextLvl();
	bool isGameOver();

	void setConsoleDimensions(int height, int width);
	int getConsoleHeight();
	int getConsoleWidth();
};