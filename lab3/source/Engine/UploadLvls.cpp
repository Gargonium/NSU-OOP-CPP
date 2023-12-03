#include "UploadLvls.h"

void startUpload() {
	initscr();			// init curses
	cbreak();			// disable buffering
	noecho();			// no echo
	curs_set(FALSE);	// disaable cursor
	keypad(stdscr, TRUE);
	timeout(50);

	std::ofstream fout;

	int console_height;
	int console_width;

	getmaxyx(stdscr, console_height, console_width);

	uploadLVL1(console_height, console_width, fout);
	//uploadLVL2(console_height, console_width, fout);
	//uploadLVL3(console_height, console_width, fout);
	//uploadLVL4(console_height, console_width, fout);
	//uploadLVL5(console_height, console_width, fout);

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

	int en_count = 1;
	//int tile_count = console_width * 2 + (console_height - 1) * 2 + 4 + console_width - 1;

	uploadEntity(console_height - (console_height / 3) - 2, 2, fout); // Upload Player
	uploadEntity(console_height - (console_height / 3) - 2, console_width - 2, fout); // Upload Door
	fout << en_count << std::endl;
	uploadEntity(console_height - (console_height / 3) - 2, console_width - 5, fout); // Upload Enemy
	//fout << tile_count;
	setBorder(console_height, console_width, fout);

	for (int i = 1; i < console_width - 1; i++) {
		uploadTile("F", console_height - (console_height / 3) - 1, i, fout);
	}

	fout.close();
}
