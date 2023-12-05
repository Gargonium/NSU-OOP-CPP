#include "Engine.h"

Engine::Engine() {

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	RECT r;
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, r.left, r.top, 915, 520, TRUE);

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

	lvl_num = 4;

	getmaxyx(stdscr, console_height, console_width);
	ctx.setConsoleDimensions(console_height, console_width);

	game_on = false;
	difficulty = 1;
	is_music_on = false;
	nickname = "Player";

	time_score = -1;

	Menu();
}

Engine::~Engine() {
	endwin();
}

void Engine::start() {

	game_launch_time = now();

	switch (difficulty) {
	case 1: player.setLives(10); break;
	case 2: player.setLives(5); break;
	case 3: player.setLives(3); break;
	default: break;
	}

	lvl_count = 1;

	readLevel();
	char c;
	while ((char)ESC_CODE != (c = getch()) && game_on) {
		c = getch();
		clear();
		ctx.setInput(c);

		action(&ctx);
		draw();

		if (ctx.isNextLvl()) {
			lvl_count++;
			if (lvl_count > lvl_num) {
				game_on = false;
				clear();
				endwin();
				std::cout << "You win" << std::endl;
				system("pause");
				break;
			}
			ctx.NextLvl(false);
			clear();
			readLevel();
		}

		if (ctx.isGameOver()) {
			game_on = false;
			clear();
			endwin();
			std::cout << "You lose" << std::endl;
			system("pause");
			break;
		}

		refresh();
	}

	Menu();
}

void Engine::action(GameContext* ctx) {
	time_score = (now() - game_launch_time) / 1s;
	player.action(ctx);
	for (Enemy& en : enemies) {
		en.action(ctx);
	}
}

void Engine::draw() {
	out(1, 1, nickname);
	out(3, 1, "Time: %ds", time_score);

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
	case 2: lvl_path = "C:/CppProjects/nvotintsev-22205/lab3/levels/level2.mp"; break;
	case 3: lvl_path = "C:/CppProjects/nvotintsev-22205/lab3/levels/level3.mp"; break;
	case 4: lvl_path = "C:/CppProjects/nvotintsev-22205/lab3/levels/level4.mp"; break;
	default: break;
	}

	std::ifstream fin;
	fin.open(lvl_path);
	
	int enemies_count;

	level.clear();
	enemies.clear();
	ctx.clear();

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

void Engine::Menu() {
	std::string gameName_string = "VERY \"FUN\" PLATFORMER";
	std::string play_string = "Play";
	std::string settings_string = "Settings";
	std::string leaderborad_string = "LeaderBoard (in progress)";
	std::string exit_string = "Exit";
	int chosen_string = 1;

	bool next_page = false;

	char c;

	while (!next_page) {
		c = getch();
		clear();
		out((console_height / 2) - 5, (console_width - gameName_string.length() - 3) / 2, gameName_string);
		out((console_height / 2) - 2, (console_width / 2) - 6, play_string);
		out((console_height / 2) - 1, (console_width / 2) - 6, settings_string);
		out((console_height / 2), (console_width / 2) - 6, leaderborad_string);
		out((console_height / 2) + 1, (console_width / 2) - 6, exit_string);

		switch ((char)c) {
		case 'w':
			if (chosen_string != 1) {
				chosen_string--;
			}
			break;
		case 's':
			if (chosen_string != 4) {
				chosen_string++; 
			}
			break;
		case '\n':
			switch (chosen_string) {
			case 1: game_on = true; next_page = true; start(); break;
			case 2: next_page = true; Settings(); break;
			//case 3: next_page = true; LeaderBoard(); break;
			case 4: exit(0); break;
			default: break;
			}
			break;
		default: break;
		}

		switch (chosen_string) {
		case 1:
			out((console_height / 2) - 2, (console_width / 2) - 8, "> ");
			break;
		case 2:
			out((console_height / 2) - 1, (console_width / 2) - 8, "> ");
			break;
		case 3:
			out((console_height / 2), (console_width / 2) - 8, "> ");
			break;
		case 4:
			out((console_height / 2) + 1, (console_width / 2) - 8, "> ");
			break;
		default: break;
		}

		refresh();
	}
}

void Engine::Settings() {
	std::string settings_string = "Settings";
	std::string nickname_string = "NickName";
	std::string difficulty_string = "Difficulty";
	std::string music_string = "Music";
	std::string back_string = "Back";

	std::string easy_string = "| Easy >";
	std::string medium_string = "< Medium >";
	std::string hard_string = "< Hard |";

	std::string off_string = "| Off >";
	std::string on_string = "< On |";
	int chosen_string = 1;

	bool prev_page = false;

	bool animation_on = true;

	bool entering_nickname = false;

	steady_clock_t last_time_ = now();

	char c;

	while (!prev_page) {
		c = getch();
		clear();
		out((console_height / 2) - 5, (console_width - settings_string.length() - 3) / 2, settings_string);
		out((console_height / 2) - 2, (console_width / 2) - 6, nickname_string);
		out((console_height / 2) - 1, (console_width / 2) - 6, difficulty_string);
		out((console_height / 2), (console_width / 2) - 6, music_string);
		out((console_height / 2) + 1, (console_width / 2) - 6, back_string);

		out((console_height / 2) - 2, (console_width / 2) + 6, nickname);

		switch (difficulty) {
		case 1: out((console_height / 2) - 1, (console_width / 2) + 6, easy_string); break;
		case 2: out((console_height / 2) - 1, (console_width / 2) + 6, medium_string); break;
		case 3: out((console_height / 2) - 1, (console_width / 2) + 6, hard_string); break;
		default: break;
		}

		if (is_music_on) {
			out((console_height / 2), (console_width / 2) + 6, on_string);
		}
		else {
			out((console_height / 2), (console_width / 2) + 6, off_string);
		}

		if (entering_nickname) {
			out((console_height / 2) - 2, (console_width / 2) - 8, "> ");
			if ((now() - last_time_) / 1ms > 500) {
				animation_on ? animation_on = false : animation_on = true;
				last_time_ = now();
			}
			if (animation_on) {
				out((console_height / 2) - 2, (console_width / 2) + 6 + nickname.length(), "_");
			}

			if ((char)c == '\n') {
				if (nickname.length() != 0) {
					entering_nickname = false;
				}
			}
			else if (c == 8) { // BackSpace
				if (nickname.length() != 0) {
					nickname.pop_back();
				}
			}

			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
				nickname.push_back(c);
			}
		}
		else {
			switch ((char)c) {
			case 'w':
				if (chosen_string != 1) {
					chosen_string--;
				}
				break;
			case 's':
				if (chosen_string != 4) {
					chosen_string++;
				}
				break;
			case 'a':
				if (chosen_string == 2) {
					if (difficulty != 1) {
						difficulty--;
					}
				}
				else if (chosen_string == 3) {
					if (is_music_on) {
						is_music_on = false;
					}
				}
				break;
			case 'd':
				if (chosen_string == 2) {
					if (difficulty != 3) {
						difficulty++;
					}
				}
				else if (chosen_string == 3) {
					if (!is_music_on) {
						is_music_on = true;
					}
				}
				break;
			case '\n':
				if (chosen_string == 1) {
					entering_nickname ? entering_nickname = false : entering_nickname = true;
				}
				else if (chosen_string == 4) {
					prev_page = true;
					Menu();
				}
				break;
			default: break;
			}

			switch (chosen_string) {
			case 1:
				out((console_height / 2) - 2, (console_width / 2) - 8, "> ");
				break;
			case 2:
				out((console_height / 2) - 1, (console_width / 2) - 8, "> ");
				break;
			case 3:
				out((console_height / 2), (console_width / 2) - 8, "> ");
				break;
			case 4:
				out((console_height / 2) + 1, (console_width / 2) - 8, "> ");
				break;
			default: break;
			}
		}

		refresh();
	}
}

void Engine::LeaderBoard() {
	
}
