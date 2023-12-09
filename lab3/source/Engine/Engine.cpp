#include "Engine.h"

Engine::Engine() {

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	RECT r;
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, r.left, r.top, 912, 520, TRUE);

	initscr();			// init curses
	cbreak();			// disable buffering
	noecho();			// no echo
	curs_set(FALSE);	// disable cursor
	keypad(stdscr, TRUE);
	timeout(50);

	lvl_num = 4;

	getmaxyx(stdscr, console_height, console_width);
	ctx.setConsoleDimensions(console_height, console_width);

	game_on = false;
	difficulty = 1;
	is_music_on = true;
	nickname = "Player";

	time_score = -1;

	leaderboard_path = "../../files/leaderboard.ld";

	level1_path = "../../files/levels/level1.mp";
	level2_path = "../../files/levels/level2.mp";
	level3_path = "../../files/levels/level3.mp";
	level4_path = "../../files/levels/level4.mp";

	en_mus_path = "../../files/music/enemy_sound.wav";
	bg_mus_path = "../../files/music/background_music.wav";
	walk_mus_path = "../../files/music/walk_sound.wav";
	menu_mus_path = "../../files/music/menu_sound.wav";
	death_mus_path = "../../files/music/death_sound.wav";
	door_mus_path = "../../files/music/door_sound.wav";

	ctx.setMusicPaths(en_mus_path, walk_mus_path, death_mus_path, door_mus_path);
}

Engine::~Engine() {
	endwin();
}

void Engine::start() {

	ctx.setMusicStatus(is_music_on);
	ctx.setDifficulty(difficulty);

	if (is_music_on) {
		
	}

	game_launch_time = now();

	switch (difficulty) {
	case 1: player.setLives(10); break;
	case 2: player.setLives(5); break;
	case 3: player.setLives(3); break;
	default: break;
	}

	lvl_count = 1;

	ctx.GameOver(false);
	ctx.NextLvl(false);

	readLevel();
	char c;
	while ((char)ESC_CODE != (c = getch()) && game_on) {
		clear();
		ctx.setInput(std::tolower(static_cast<unsigned char>(c)));

		action(&ctx);
		draw();

		if (ctx.isNextLvl()) {
			lvl_count++;
			if (lvl_count > lvl_num) {
				game_on = false;
				clear();
				out(0, 0, "You win");
				refresh();
				updateLeaderBoard(true);
				Sleep(100);
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
			Sleep(100);
			system("pause");
			break;
		}

		refresh();
	}

	if (is_music_on) {
		
	}
	game_on = false;
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
	for (Tile& tile : lvl_border) {
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
	case 1: lvl_path = level1_path; break;
	case 2: lvl_path = level2_path; break;
	case 3: lvl_path = level3_path; break;
	case 4: lvl_path = level4_path; break;
	default: break;
	}

	std::ifstream fin(lvl_path);
	
	int enemies_count;

	int border_count;

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

		fin >> border_count;

		Tile temp;
		std::string s;
		
		for (int i = 0; i < border_count; i++) {
			fin >> n_y >> n_x >> s;
			temp.setY(n_y);
			temp.setX(n_x);
			temp.setSym(s);
			lvl_border.push_back(temp);
		}

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
	std::string leaderboard_string = "LeaderBoard";
	std::string exit_string = "Exit";
	int chosen_string = 1;

	bool next_play = false;
	bool next_set = false;
	bool next_leader = false;

	char c;

	while (!next_play && !next_set && !next_leader) {
		c = std::tolower(static_cast<unsigned char>(getch()));
		clear();
		out((console_height / 2) - 5, (console_width - gameName_string.length() - 3) / 2, gameName_string);
		out((console_height / 2) - 2, (console_width / 2) - 6, play_string);
		out((console_height / 2) - 1, (console_width / 2) - 6, settings_string);
		out((console_height / 2), (console_width / 2) - 6, leaderboard_string);
		out((console_height / 2) + 1, (console_width / 2) - 6, exit_string);

		switch ((char)c) {
		case 'ö':
		case 'w':
			if (chosen_string != 1) {
				chosen_string--;
			}
			else {
				chosen_string = 4;
			}
			break;
		case 'û':
		case 's':
			if (chosen_string != 4) {
				chosen_string++; 
			}
			else {
				chosen_string = 1;
			}
			break;
		case '\n':
			if (is_music_on) {
				
			}
			switch (chosen_string) {
			case 1: next_play = true; break;
			case 2: next_set = true; break;
			case 3: endwin(); next_leader = true; break;
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

	if (next_play) {
		game_on = true;
		start();
	}
	else if (next_set) {
		Settings();
	}
	else if (next_leader) {
		LeaderBoard();
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
		c = std::tolower(static_cast<unsigned char>(getch()));
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

			if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) && nickname.length() < 10) {
				nickname.push_back(c);
			}
		}
		else {
			switch ((char)c) {
			case 'ö':
			case 'w':
				if (chosen_string != 1) {
					chosen_string--;
				}
				else {
					chosen_string = 4;
				}
				break;
			case 'û':
			case 's':
				if (chosen_string != 4) {
					chosen_string++;
				}
				else {
					chosen_string = 1;
				}
				break;
			case 'ô':
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
			case 'â':
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
					if (is_music_on) {
						
					}
					prev_page = true;
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

	if (prev_page) {
		Menu();
	}
}

void Engine::LeaderBoard() {

	std::ifstream fin(leaderboard_path);

	std::string name;
	std::string diff;
	int time = 0;

	if (leader_board.size() == 0) {
		while (fin >> name >> diff >> time) {
			leader_board.push_back({ name, diff, time });
		}
	}

	std::sort(leader_board.begin(), leader_board.end(),
		[](std::tuple<std::string, std::string, int> a, std::tuple<std::string, std::string, int> b) {return std::get<2>(a) < std::get<2>(b); });

	updateLeaderBoard(false);

	fin.close();

	std::string leaderboard_string = "LeaderBoard";
	std::string back_string = "Back";
	std::string clear_string = "Clear";

	bool prev_page = false;

	int chosen_string = 1;

	char c;

	while (!prev_page) {
		c = std::tolower(static_cast<unsigned char>(getch()));
		clear();

		out((console_height / 2) - 7, (console_width - leaderboard_string.length() - 3) / 2, leaderboard_string);

		out((console_height / 2) + 7, (console_width / 2) - 18, back_string);
		out((console_height / 2) + 7, (console_width / 2) + 11, clear_string);

		out((console_height / 2) - 5, (console_width / 2) - 18, "N  Name       Difficulty      Time");

		for (int i = 0; (i < 10) && (i < leader_board.size()); i++) {
			std::tie(name, diff, time) = leader_board[i];
			out((console_height / 2) - 4 + i, (console_width / 2) - 18, "%d  ", i + 1);
			out((console_height / 2) - 4 + i, (console_width / 2) - 15, name);
			out((console_height / 2) - 4 + i, (console_width / 2) - 4, diff);
			out((console_height / 2) - 4 + i, (console_width / 2) + 11, " %ds", time);
		}
		if (leader_board.size() < 10) {
			for (int i = 0; i < (10 - leader_board.size()); i++) {
				out((console_height / 2) - 4 + leader_board.size() + i, (console_width / 2) - 18, "%d ", i + 1 + leader_board.size());
			}
		}

		switch ((char)c) {
		case 'ö':
		case 'w':
			if (chosen_string == 12) {
				chosen_string = 10;
			}
			else if (chosen_string != 1) {
				chosen_string--;
			}
			else {
				chosen_string = 11;
			}
			break;
		case 'û':
		case 's':
			if (chosen_string == 11 || chosen_string == 12) {
				chosen_string = 1;
			}
			else {
				chosen_string++;
			}
			break;
		case 8: // BackSpace
			if (chosen_string < 11) {
				leader_board.erase(leader_board.begin() + chosen_string - 1);
				updateLeaderBoard(false);
			}
			break;
		case 'â':
		case 'ô':
		case 'd':
		case 'a':
			if (chosen_string == 11) {
				chosen_string = 12;
			}
			else if (chosen_string == 12) {
				chosen_string = 11;
			}
			break;
		case '\n':
			if (chosen_string == 11) {
				if (is_music_on) {
					
				}
				prev_page = true;
			}
			else if (chosen_string == 12) {
				leader_board.clear();
				updateLeaderBoard(false);
			}
			break;
		default: break;
		}

		switch (chosen_string) {
		case 1:
			out((console_height / 2) - 4, (console_width / 2) - 20, "> ");
			break;
		case 2:
			out((console_height / 2) - 3, (console_width / 2) - 20, "> ");
			break;
		case 3:
			out((console_height / 2) - 2, (console_width / 2) - 20, "> ");
			break;
		case 4:
			out((console_height / 2) - 1, (console_width / 2) - 20, "> ");
			break;
		case 5:
			out((console_height / 2), (console_width / 2) - 20, "> ");
			break;
		case 6:
			out((console_height / 2) + 1, (console_width / 2) - 20, "> ");
			break;
		case 7:
			out((console_height / 2) + 2, (console_width / 2) - 20, "> ");
			break;
		case 8:
			out((console_height / 2) + 3, (console_width / 2) - 20, "> ");
			break;
		case 9:
			out((console_height / 2) + 4, (console_width / 2) - 20, "> ");
			break;
		case 10:
			out((console_height / 2) + 5, (console_width / 2) - 20, "> ");
			break;
		case 11:
			out((console_height / 2) + 7, (console_width / 2) - 20, "> ");
			break;
		case 12:
			out((console_height / 2) + 7, (console_width / 2) + 9, "> ");
			break;
		default: break;
		}

		refresh();
	}
	if (prev_page) {
		Menu();
	}
}

void Engine::updateLeaderBoard(bool is_new) {
	std::ofstream fout;
	if (is_new) {
		fout.open(leaderboard_path, std::ios::binary | std::ios::out | std::ios::app);
		std::string diff;
		switch (difficulty) {
		case 1: diff = "Easy"; break;
		case 2: diff = "Medium"; break;
		case 3: diff = "Hard"; break;
		default: break;
		}
		fout << nickname << " " << diff << " " << time_score << std::endl;
	}
	else {
		fout.open(leaderboard_path, std::ios::binary | std::ios::out | std::ios::trunc);
		std::string name;
		std::string diff;
		int time = 0;
		if (leader_board.size() == 0) {
			fout << std::endl;
		}
		for (int i = 0; i < leader_board.size(); i++) {
			std::tie(name, diff, time) = leader_board[i];
			fout << name << " " << diff << " " << time << std::endl;
		}
	}
	fout.close();
}