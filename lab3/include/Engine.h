#pragma once

#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Globals.h"
#include "Player.h"
#include "Box.h"

#include <thread>

class Engine:public Player, public Box{
private:

	void input();

	void update();

	void draw();

	Box box;

	Player player;

	bool is_open;

	int delay;

	INPUT_RECORD InputRecord;
	DWORD Events; 
	DWORD prev_mode;
	HANDLE hStdIn;

	uint64_t current_timestamp();

	void KeyEventProc(KEY_EVENT_RECORD);
	void MouseEventProc(MOUSE_EVENT_RECORD);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

public:
	Engine();

	~Engine();

	void start();
};
