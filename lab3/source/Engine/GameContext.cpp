#include "GameContext.h"

GameContext::GameContext() {
	next_lvl = false;
	game_over = false;
}

void GameContext::setInput(char c) {
	input = c;
}

char GameContext::getInput() {
	return input;
}

bool GameContext::isGameOver() {
	return game_over;
}

bool GameContext::isNextLvl() {
	return next_lvl;
}

void GameContext::NextLvl(bool is_true) {
	next_lvl = is_true;
}

void GameContext::GameOver(bool is_true) {
	game_over = is_true;
}

void GameContext::setPlayerCoords(int y, int x) {
	player_coords = { y, x };
}

void GameContext::setDoorCoords(int y, int x) {
	door_coords = { y, x };
}

void GameContext::setEnemiesCoords(int id, int y, int x) {
	enemies_coords.at(id) = { y, x };
}

void GameContext::setEnemiesCoords(std::vector<std::tuple<int, int>> coords) {
	enemies_coords = coords;
}

void GameContext::setTilesCoords(std::vector<std::tuple<int, int>> coords) {
	tiles_coords = coords;
}

std::tuple<int, int> GameContext::getPlayerCoords() {
	return player_coords;
}

std::tuple<int, int> GameContext::getDoorCoords() {
	return door_coords;
}

std::vector<std::tuple<int, int>> GameContext::getEnemiesCoords() {
	return enemies_coords;
}

std::vector<std::tuple<int, int>> GameContext::getTilesCoords() {
	return tiles_coords;
}

void GameContext::setConsoleDimensions(int height, int width) {
	console_height = height;
	console_width = width;
}

int GameContext::getConsoleHeight() {
	return console_height;
}

int GameContext::getConsoleWidth() {
	return console_width;
}

void GameContext::clear() {
	enemies_coords.clear();
	tiles_coords.clear();
}

void GameContext::setMusicPaths(char* enemy, char* walk, char* death, char* door) {
	en_mus_path = enemy;
	walk_mus_path = walk;
	death_mus_path = death;
	door_mus_path = door;
};
char* GameContext::getEnemyMusic() {
	return en_mus_path;
};
char* GameContext::getWalkMusic() {
	return walk_mus_path;
};
char* GameContext::getDeathMusic() {
	return death_mus_path;
};
char* GameContext::getDoorMusic() {
	return door_mus_path;
};

void GameContext::setMusicStatus(bool is_true) {
	is_music_on = is_true;
}

bool GameContext::getMusicStatus() {
	return is_music_on;
}

void GameContext::setDifficulty(int diff) {
	difficulty = diff;
}

int GameContext::getDifficulty() {
	return difficulty;
}