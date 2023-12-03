#include "Door.h"

void Door::action(GameContext* ctx) {
	
}

void Door::draw() {
	out(getY(), getX(), "D");
}