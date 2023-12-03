#include "Tile.h"

void Tile::action(GameContext* ctx) {

}

void Tile::draw() {
	out(getY(), getX(), symbol);
}

void Tile::setSym(std::string s) {
	symbol = s;
}

std::string Tile::getSym() {
	return symbol;
}