#pragma once
#include "Canvas.h"

class Player : public Canvas {
protected:
	int pl_x;
	int pl_y;
	int difficulty;

public:
	Player(int diff);

	Player();

	void renderPlayer(Canvas &can);

	int getXCoordinate();

	int getYCoordinate();

	void clearPlayer(Canvas& can);

	void moveLeft(Canvas& can);

	void moveRight(Canvas& can);

	void moveUp(Canvas& can);

	void moveDown(Canvas& can);
};
