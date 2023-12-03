#pragma once

#include "GameObject.h"
#include "GameContext.h"

class Door : public GameObject {
public:
	void action(GameContext* ctx);
	void draw();
};