#include "Box.h"

Box::Box() {
	/*m_width = getConsoleWidth();
	m_height = getConsoleHeight();*/
	
	m_width = 40;
	m_height = 20;

	m_field_floor = '-';

	m_changes.changes = new CHANGE[m_height * m_width];
	m_changes.changes_count = 0;
	
	field = new char* [m_height];
	for (int i = 0; i < m_height; i++) {
		field[i] = new char[m_width];
	}

	level = new Floor[m_height * m_width];
	floor_count = 0;

	for (int i = 0; i < 3 * m_width / 4; i++) {
		level[i].setX(i);
		level[i].setY(m_height - 1);
		glv::makeChange(m_changes, i, m_height - 1, m_field_floor);
		floor_count++;
	}
	
	for (int i = 3 * m_width / 4; i < m_width; i++) {
		level[i].setX(i);
		level[i].setY(m_height - 1 - i + (3 * m_width / 4));
		glv::makeChange(m_changes, i, m_height - 1 - i + (3 * m_width / 4), m_field_floor);
		floor_count++;
	}
};

Box::~Box() {
	for (int i = 0; i < m_height; i++) {
		delete[] field[i];
	}
	delete[] field;
	delete[] m_changes.changes;
	delete[] level;
};

int Box::getConsoleWidth() {
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int width = rc.right;
	return width;
};

int Box::getConsoleHeight() {
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int height = rc.bottom;
	return height;
};

void Box::updateDimensions() {
	int new_width = getConsoleWidth();
	int new_height = getConsoleHeight();
	if ((m_width != new_width) || (m_height != new_width)) {
		m_width = new_width;	
		m_height = new_height;
	}
};

int Box::getHeight() {
	return m_height;
}

int Box::getWidth() {
	return m_width;
}

void Box::writeToField(CHANGE ch) {
	field[ch.coord.Y][ch.coord.X] = ch.symbol;
}

Floor* Box::getLevel() {
	return level;
}

int Box::getFloorCount() {
	return floor_count;
}

//void Box::updateBox() {
//
//	// updateDimensions();
//
//	// SetConsoleCursorPosition(hStdOut, makeCoord(0, 0));
//
//
//
//	// «десь надо реализовать вывод массива field
//	// ¬озможно стоит создать ещЄ один массив в котором будут хранитс€ изменени€, чтобы не обновл€ть это каждый ебаный раз
//	// Ќадо пон€ть зачем мне нужна функци€ draw, потому что по хорошему здесь надо не вывод массива делать,
//	// а только внесение изменений из массива изменений в массив field, а отрисовывать уже в draw.
//	// » наверное избавитьс€ нахуй от updateDimensions, т.к. это сложна€ штука и надо тогда не только изменени€ отрисовывать,
//	// а полностью все поле
//
//	// ’от€ оп€ть же, если здесь € буду вносить изменени€, то как € пойму что именно нужно отрисовывать. 
//	// ¬озможно передовать координаты в каком-то формате и количество изменений. Ёто пока только иде€
//
//};
