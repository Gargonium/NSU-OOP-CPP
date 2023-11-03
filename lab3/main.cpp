#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Bullet.h"
#include "Player.h"
#include "Canvas.h"
#include "Enemy.h"

using namespace std;

int difficultyScreen() {
	cout << "Choose the difficulty level\n1: Very Hard\n2: Hard\n3: Medium\n4: Easy\n";
	int difficulty;
	cin >> difficulty;
	return difficulty;
}

void pressAnyButton() {
	cout << "Press any button to continue";
	while (!_kbhit()) {}
}

void controlScreen() {
	system("cls");
	cout << "Control:" << endl;
	cout << "W - Up\nS - Down\nA - Left\nD - Right\nSpace - Fire" << endl;
	pressAnyButton();
}

int main() {

	int difficulty = difficultyScreen();

	Canvas can(difficulty);
	Player pl(difficulty);

	controlScreen();

	can.renderCanvas();
	pl.renderPlayer(can);

	Bullet bullet(pl);

	Enemy en;

	en.renderEnemy(can);

	bool bulfly = false;
	bool setbulcor = false;
	int enemy_fps = difficulty * 2;
	bool is_win = false;

	while (!is_win) {
		Sleep(100);
		
		if (_kbhit()) {
			int c = _getch();

			switch ((char) c) {
			case 'w': 
				pl.moveUp(can);
				break;
			case 'a': 
				pl.moveLeft(can);
				break;
			case 's': 
				pl.moveDown(can);
				break;
			case 'd': 
				pl.moveRight(can);
				break;
			case ' ': 
				if (!bulfly) {
					bulfly = true;
					setbulcor = true;
				}
				break;	
			case 'Q':
				is_win = true;
				break;
			default: 
				break;
			}

			if (c == 27) {
				break;
			}
		}

		if (bulfly) {
			if (setbulcor) {
				bullet.setBulletCoordinates(pl);
				setbulcor = false;
			}
			bulfly = bullet.bulletFly(pl, can, en);
		}

		if (enemy_fps == 0) {
			en.movement(can);
			enemy_fps = difficulty;
		}
		else {
			enemy_fps--;
		}

		if (difficulty * 10 == can.getScore()) {
			is_win = true;
		}

	}

	system("cls");
	if (is_win) {
		//cout << "YOU ARE THE WINNER!!!" << endl;
		Sleep(300);
		cout << "\tWINNER" << endl;
		Sleep(300); 
		cout << "\tWINNER" << endl; 
		Sleep(300);
		cout << "\tCHICKEN" << endl;
		Sleep(300);
		cout << "\tDINNER" << endl;
	}
	else {
		cout << "Pathetic loser...";
	}

	pressAnyButton();

	return 0;
}
