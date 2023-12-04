#include "UploadLvls.h"

void startUpload() {
	initscr();			// init curses
	cbreak();			// disable buffering
	noecho();			// no echo
	curs_set(FALSE);	// disaable cursor
	keypad(stdscr, TRUE);
	timeout(50);

	std::ofstream fout;

	int console_height = 30; // 30
	int console_width = 120; // 120

	uploadLVL1(console_height, console_width, fout);
	uploadLVL2(console_height, console_width, fout);
	uploadLVL3(console_height, console_width, fout);
	uploadLVL4(console_height, console_width, fout);

	endwin();
}

void uploadTile(std::string s, int y, int x, std::ofstream& fout) {
	fout << y << " " << x << " " << s << std::endl;
}

void uploadEntity(int y, int x, std::ofstream& fout) {
	fout << y << " " << x << std::endl;
}

void setBorder(int console_height, int console_width, std::ofstream& fout) {
	for (int i = 0; i < console_width; i++) {
		uploadTile("-", console_height - 1, i, fout);
		uploadTile("-", 0, i, fout);
	}
	for (int i = 0; i < console_height - 1; i++) {
		uploadTile("|", i, console_width - 1, fout);
		uploadTile("|", i, 0, fout);
	}
	uploadTile("+", console_height - 1, console_width - 1, fout);
	uploadTile("+", 0, console_width - 1, fout);
	uploadTile("+", console_height - 1, 0, fout);
	uploadTile("+", 0, 0, fout);
}

void uploadLVL1(int console_height, int console_width, std::ofstream& fout) {
	fout.open("C:/CppProjects/nvotintsev-22205/lab3/levels/level1.mp", std::ios::binary | std::ios::out);

	int en_count = 0;
	uploadEntity(19, 2, fout); // Upload Player
	uploadEntity(19, 118, fout); // Upload Door
	fout << en_count << std::endl;

	setBorder(30, 120, fout);
	for (int i = 0; i < 30; i++) {
		uploadTile("F", 20, 1 + i, fout);
	}
	uploadTile("F", 19, 32, fout);
	uploadTile("F", 19, 33, fout);
	uploadTile("F", 18, 35, fout);
	uploadTile("F", 18, 36, fout);
	uploadTile("F", 18, 38, fout);
	uploadTile("F", 18, 39, fout);
	uploadTile("F", 19, 41, fout);
	uploadTile("F", 19, 42, fout);
	for (int i = 0; i < 22; i++) {
		uploadTile("F", 20, 44 + i, fout);
	}
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 19, 66 + i, fout);
	}
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 18, 70 + i, fout);
	}
	for (int i = 0; i < 15; i++) {
		uploadTile("F", 17, 74 + i, fout);
	}
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 18, 89 + i, fout);
	}
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 19, 93 + i, fout);
	}
	for (int i = 0; i < 22; i++) {
		uploadTile("F", 20, 97 + i, fout);
	}
	fout.close();
}

void uploadLVL2(int console_height, int console_width, std::ofstream& fout) {
	fout.open("C:/CppProjects/nvotintsev-22205/lab3/levels/level2.mp", std::ios::binary | std::ios::out);

	int en_count = 1;
	uploadEntity(19, 2, fout); // Upload Player
	uploadEntity(19, 118, fout); // Upload Door
	fout << en_count << std::endl;
	uploadEntity(19, 68, fout); // Upload Enemy

	setBorder(30, 120, fout);
	for (int i = 0; i < 30; i++) {
		uploadTile("F", 20, 1 + i, fout);
	}
	uploadTile("F", 19, 33, fout);
	uploadTile("F", 19, 34, fout);
	uploadTile("F", 17, 35, fout);
	uploadTile("F", 17, 36, fout);
	for (int i = 0; i < 30; i++) {
		uploadTile("F", 20, 40 + i, fout);
	}
	uploadTile("F", 19, 72, fout);
	uploadTile("F", 19, 73, fout);
	uploadTile("F", 18, 75, fout);
	uploadTile("F", 18, 76, fout);
	uploadTile("F", 17, 78, fout);
	uploadTile("F", 17, 79, fout);
	uploadTile("F", 16, 81, fout);
	uploadTile("F", 16, 82, fout);
	uploadTile("F", 15, 84, fout);
	uploadTile("F", 15, 85, fout);
	uploadTile("F", 14, 87, fout);
	uploadTile("F", 14, 88, fout);
	uploadTile("F", 20, 91, fout);
	uploadTile("F", 20, 93, fout);
	uploadTile("F", 20, 95, fout);
	for (int i = 0; i < 22; i++) {
		uploadTile("F", 20, 97 + i, fout);
	}

	fout.close();
}

void uploadLVL3(int console_height, int console_width, std::ofstream& fout) {
	fout.open("C:/CppProjects/nvotintsev-22205/lab3/levels/level3.mp", std::ios::binary | std::ios::out);

	int en_count = 2;
	uploadEntity(18, 2, fout); // Upload Player
	uploadEntity(19, 118, fout); // Upload Door
	fout << en_count << std::endl;
	uploadEntity(19, 27, fout); // Upload Enemy
	uploadEntity(19, 67, fout);

	setBorder(30, 120, fout);
	uploadTile("F", 19, 1, fout);
	uploadTile("F", 19, 2, fout);
	for (int i = 0; i < 28; i++) {
		uploadTile("F", 20, 3 + i, fout);
	}
	uploadTile("F", 19, 31, fout);
	uploadTile("F", 19, 32, fout);
	uploadTile("F", 18, 33, fout);
	uploadTile("F", 18, 34, fout);
	uploadTile("F", 17, 35, fout);
	uploadTile("F", 17, 36, fout);
	uploadTile("F", 17, 42, fout);
	uploadTile("F", 17, 43, fout);
	uploadTile("F", 18, 44, fout);
	uploadTile("F", 18, 45, fout);
	uploadTile("F", 19, 46, fout);
	uploadTile("F", 19, 47, fout);
	for (int i = 0; i < 22; i++) {
		uploadTile("F", 20, 48 + i, fout);
	}
	uploadTile("F", 19, 71, fout);
	uploadTile("F", 18, 73, fout);
	uploadTile("F", 17, 75, fout);
	uploadTile("F", 16, 77, fout);
	uploadTile("F", 15, 79, fout);
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 16, 90 + i, fout);
	}
	uploadTile("F", 17, 95, fout);
	uploadTile("F", 17, 96, fout);
	uploadTile("F", 18, 98, fout);
	uploadTile("F", 18, 99, fout);
	uploadTile("F", 19, 102, fout);
	for (int i = 0; i < 15; i++) {
		uploadTile("F", 20, 104 + i, fout);
	}

	fout.close();
}

void uploadLVL4(int console_height, int console_width, std::ofstream& fout) {
	fout.open("C:/CppProjects/nvotintsev-22205/lab3/levels/level4.mp", std::ios::binary | std::ios::out);

	int en_count = 4;
	uploadEntity(18, 2, fout); // Upload Player
	uploadEntity(21, 54, fout); // Upload Door
	fout << en_count << std::endl;
	uploadEntity(8, 60, fout); // Upload Enemy
	uploadEntity(14, 60, fout);
	uploadEntity(22, 61, fout);
	uploadEntity(22, 88, fout);

	setBorder(30, 120, fout);
	for (int i = 0; i < 20; i++) {
		uploadTile("F", 20, 1 + i, fout);
	}
	uploadTile("F", 19, 22, fout);
	uploadTile("F", 19, 23, fout);
	uploadTile("F", 18, 25, fout);
	uploadTile("F", 18, 26, fout);
	uploadTile("F", 17, 28, fout);
	uploadTile("F", 17, 29, fout);
	uploadTile("F", 16, 31, fout);
	uploadTile("F", 16, 32, fout);
	uploadTile("F", 14, 33, fout);
	uploadTile("F", 14, 34, fout);
	uploadTile("F", 13, 36, fout);
	uploadTile("F", 13, 37, fout);
	uploadTile("F", 12, 39, fout);
	uploadTile("F", 12, 40, fout);
	uploadTile("F", 10, 41, fout); 
	uploadTile("F", 10, 42, fout);
	uploadTile("F", 14, 41, fout);
	uploadTile("F", 14, 42, fout);
	for (int i = 0; i < 40; i++) {
		uploadTile("F", 9, 43 + i, fout);
		uploadTile("F", 15, 43 + i, fout);
	}
	uploadTile("F", 10, 84, fout);
	uploadTile("F", 10, 85, fout);
	uploadTile("F", 14, 83, fout);
	uploadTile("F", 14, 84, fout);
	uploadTile("F", 14, 85, fout);
	uploadTile("F", 13, 86, fout);
	uploadTile("F", 13, 87, fout);
	uploadTile("F", 13, 88, fout);
	for (int i = 0; i < 16; i++) {
		uploadTile("F", 12, 89 + i, fout);
	}
	uploadTile("F", 13, 106, fout);
	uploadTile("F", 13, 107, fout);
	uploadTile("F", 14, 109, fout);
	uploadTile("F", 14, 110, fout);
	uploadTile("F", 15, 112, fout);
	uploadTile("F", 15, 113, fout);

	uploadTile("F", 22, 54, fout);
	uploadTile("F", 22, 55, fout);
	uploadTile("F", 22, 56, fout);
	for (int i = 0; i < 30; i++) {
		uploadTile("F", 23, 59 + i, fout);
	}
	uploadTile("F", 23, 90, fout);
	uploadTile("F", 23, 91, fout);
	uploadTile("F", 22, 92, fout);
	uploadTile("F", 22, 93, fout);
	for (int i = 0; i < 11; i++) {
		uploadTile("F", 21, 94 + i, fout);
	}
	uploadTile("F", 20, 106, fout);
	uploadTile("F", 20, 107, fout);
	uploadTile("F", 19, 109, fout);
	uploadTile("F", 19, 110, fout);
	uploadTile("F", 18, 112, fout);
	uploadTile("F", 18, 113, fout);
	uploadTile("F", 18, 114, fout);
	for (int i = 0; i < 4; i++) {
		uploadTile("F", 17, 115 + i, fout);
	}

	fout.close();
}
