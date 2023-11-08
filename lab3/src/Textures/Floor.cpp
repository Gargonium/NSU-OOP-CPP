#include "Floor.h"

Floor::Floor() {
	m_x = 0;
	m_y = 0;
}

Floor::Floor(int x, int y) {
	m_x = x;
	m_y = y;
}

Floor::~Floor() {

}

int Floor::getX() {
	return m_x;
}

int Floor::getY() {
	return m_y;
}

void Floor::setX(int x) {
	m_x = x;
}

void Floor::setY(int y) {
	m_y = y;
}
