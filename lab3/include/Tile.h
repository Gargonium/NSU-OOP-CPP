#pragma once

#include "GameObject.h"
#include "GameContext.h"

class Tile : public GameObject {
private:
	std::string symbol;
public:
	void action(GameContext* ctx);
	void draw();
	void setSym(std::string s);
	std::string getSym();
};