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

void GameContext::NextLvl(bool b) {
	next_lvl = b;
}

void GameContext::GameOver() {
	game_over = true;
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