#pragma once

#include <curses.h>
#include <fstream>
#include "Door.h"
#include "Enemy.h"
#include "Player.h"
#include "Tile.h"

void startUpload();

void uploadTile(std::string s, int y, int x, std::ofstream& fout);
void uploadEntity(int y, int x, std::ofstream& fout);
void uploadEntity(int y, int x, std::ofstream& fout);
void uploadEntity(int y, int x, std::ofstream& fout);

void setBorder(int console_height, int console_width, std::ofstream& fout);

void uploadLVL1(int console_height, int console_width, std::ofstream& fout);
