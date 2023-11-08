#pragma once

#include <Windows.h>
#include <iostream>

typedef struct CHANGE {
	COORD coord;
	char symbol;
}CHANGE;

typedef struct CHANGES {
	CHANGE* changes;
	int changes_count;
}CHANGES;

namespace glv {

	void drawChanges(CHANGES& ch);

	COORD makeCoord(int x, int y);

	void makeChange(CHANGES& ch, int x, int y, char c);
}