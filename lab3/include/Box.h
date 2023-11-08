#pragma once

#include "Globals.h"
#include "Floor.h"

class Box:public Floor {
private:

	CHANGES m_changes;

	int m_width;
	int m_height;
	char m_field_floor;
	char** field;

	int getConsoleWidth();

	int getConsoleHeight();

	void updateDimensions();

	Floor* level;	

	int floor_count;

public:
	Box();

	virtual ~Box();

	void updateBox();

	void drawBox();

	int getHeight();

	int getWidth();

	void writeToField(CHANGE ch);

	Floor* getLevel();

	int getFloorCount();

};
