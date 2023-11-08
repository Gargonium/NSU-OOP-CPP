#pragma once

class Floor {
private:
	int m_x;
	int m_y;
public:
	Floor();
	Floor(int x, int y);
	~Floor();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);
};
