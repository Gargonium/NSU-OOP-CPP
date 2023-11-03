#pragma once

#include "Canvas.h"

class Enemy :public Canvas {
private:
	int en_x;
	int en_y;
	bool direction;
public:

	Enemy();

	void renderEnemy(Canvas& can);

	int getX();

	int getY();

	void movement(Canvas& can);

	void shot(Canvas& can);
};
