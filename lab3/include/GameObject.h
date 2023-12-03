#pragma once

#include <chrono>
#include <curses.h>
#include <string>
#include <map>
#include <string>

#include "GameContext.h"

using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;
using namespace std::literals::chrono_literals;

class GameObject {
private:
	int x;
	int y;
public:
	virtual void action(GameContext* ctx) = 0;
	virtual void draw() = 0;
	int getY();
	int getX();
	void setY(int n_y);
	void setX(int n_x);
	void out(int y, int x, std::string s);
	void out(int y, int x, const char* s, int value);
	steady_clock_t now();
};
