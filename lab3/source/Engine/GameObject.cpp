#include "GameObject.h"

int GameObject::getX() {
	return x;
}

int GameObject::getY() {
	return y;
}

void GameObject::setX(int n_x) {
	x = n_x;
}

void GameObject::setY(int n_y) {
	y = n_y;
}

steady_clock_t GameObject::now() {
	return std::chrono::steady_clock::now();
}

void GameObject::out(int y, int x, std::string s) {
	wmove(stdscr, y, x);
	wprintw(stdscr, "%s", s.c_str());
}

void GameObject::out(int y, int x, const char* s, int value) {
	wmove(stdscr, 1, 1);
	wprintw(stdscr, s, value);
}