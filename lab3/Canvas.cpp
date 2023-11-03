#include "Canvas.h"

#include <iostream>


Canvas::Canvas() {
	field_bg = '.';
	vertical = 5;
	horizontal = 10;
	score = 0;
	difficulty = 1;

	field = new char* [vertical];
	for (int i = 0; i < vertical; i++) {
		field[i] = new char[horizontal];
		for (int j = 0; j < horizontal; j++) {
			field[i][j] = field_bg;
		}
	}
};

Canvas::Canvas(int dif) {
	field_bg = '.';
	vertical = 5;
	horizontal = 10;
	score = 0;
	difficulty = dif;

	field = new char* [vertical];
	for (int i = 0; i < vertical; i++) {
		field[i] = new char[horizontal];
		for (int j = 0; j < horizontal; j++) {
			field[i][j] = field_bg;
		}
	}
};

Canvas::~Canvas() {
	for (int i = 0; i < vertical; i++) {
		delete[] field[i];
	}
	delete[] field;
};

void Canvas::setSize(int vert, int hor) {
	this->vertical = vert * 3;
	this->horizontal = hor;
};

void Canvas::setChar(int x, int y, char c) {
	field[y][x] = c;
};	

void Canvas::incScore() {
	score++;
};

int Canvas::getScore() {
	return score;
};

void Canvas::renderCanvas() {
	system("cls");
	std::cout << "Press ESC to exit" << std::endl;
	std::cout << "Score "<< difficulty * 10 << " points to win" << std::endl;
	for (int i = 0; i < vertical; i++) {
		for (int j = 0; j < horizontal; j++) {
			std::cout << this->field[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "Score: " << score;
};
