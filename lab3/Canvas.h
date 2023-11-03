#pragma once

class Canvas {
protected:
	int score;
	int vertical;
	int horizontal;
	char field_bg;
	char** field;
	int difficulty;

public:

	void renderCanvas();

	Canvas();

	Canvas(int dif);

	~Canvas();

	int getScore();

	void setSize(int vert, int hor);

	void setChar(int x, int y, char c);

	void incScore();
	
};
