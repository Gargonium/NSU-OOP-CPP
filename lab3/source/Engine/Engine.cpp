#include "Engine.h"

Engine::Engine() {
	initscr();			// init curses
	cbreak();			// disable buffering
	noecho();			// no echo
	curs_set(FALSE);	// disaable cursor
	keypad(stdscr, TRUE);
	timeout(50);

	if (has_colors() == FALSE) {
		endwin();
		std::cerr << "Your terminal does not support colors\n";
		exit(1);
	}

	lvl_num = 1;
	lvl_count = 1;
}

Engine::~Engine() {
	endwin();
}

void Engine::start() {
	readLevel();
	char c;
	while ((char)ESC_CODE != (c = getch())) {
		clear();
		ctx.setInput(c);

		allAction(&ctx);
		allDraw();

		if (ctx.isNextLvl()) {
			lvl_count++;
			if (lvl_count > lvl_num) {
				clear;
				endwin;
				std::cout << "You win";
				break;
			}
			ctx.NextLvl(false);
			readLevel();
		}

		if (ctx.isGameOver()) {
			clear;
			endwin();
			std::cout << "You lose";
			break;
		}

		refresh();
	}
}

void Engine::allAction(GameContext* ctx) {
	player.action(ctx);
	for (Enemy& en : enemies) {
		en.action(ctx);
	}
}

void Engine::allDraw() {
	for (Tile& tile : level) {
		tile.draw();
	}
	player.draw();
	door.draw();
	for (Enemy& en : enemies) {
		en.draw();
	}
}

void Engine::readLevel() {

	char* lvl_path;

	switch (lvl_count) {
	case 1: lvl_path = "C:/CppProjects/nvotintsev-22205/lab3/levels/level1.mp"; break;
	case 2: lvl_path = "../../levels/level2.mp"; break;
	case 3: lvl_path = "../../levels/level3.mp"; break;
	case 4: lvl_path = "../../levels/level4.mp"; break;
	case 5: lvl_path = "../../levels/level5.mp"; break;
	default: break;
	}

	std::ifstream fin;
	fin.open(lvl_path);
	
	int enemies_count;

	if (fin.is_open()) {
		int n_y;
		int n_x;

		fin >> n_y >> n_x;
		player.setY(n_y);
		player.setX(n_x);
		player.setStartXY(n_y, n_x);
		ctx.setPlayerCoords(n_y, n_x);

		fin >> n_y >> n_x;
		door.setY(n_y);
		door.setX(n_x);
		ctx.setDoorCoords(n_y, n_x);

		fin >> enemies_count;
		Enemy en;
		std::vector<std::tuple<int, int>> coords;
		for (int i = 0; i < enemies_count; i++) {
			fin >> n_y >> n_x;
			en.setY(n_y);
			en.setX(n_x);
			en.setId(i);
			coords.push_back({ n_y, n_x });
			enemies.push_back(en);
		}
		ctx.setEnemiesCoords(coords);
		coords.clear();

		Tile temp;
		std::string s;
		while (fin >> n_y >> n_x >> s) {
			temp.setY(n_y);
			temp.setX(n_x);
			temp.setSym(s);
			coords.push_back({ n_y, n_x });
			level.push_back(temp);
		}
		ctx.setTilesCoords(coords);
	}

	fin.close();
}
