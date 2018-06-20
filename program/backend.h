#ifndef BACKEND_H
#define BACKEND_H

#include <cstdlib>
#include "../UI/mainUI.h"
#include <string>
#include <curses.h>
#include <iostream>
#include <ctime>

using namespace std;

void step(bool ** board, int width, int height);
void move_cursor_up();
void move_cursor_down();
void move_cursor_left();
void move_cursor_right();
int getrows();
int getcollumns();
bool ** boardSetup(int rows, int cols);
void run();
void save(bool ** board);
bool ** loadBoard(string file);
void destroyBoard(bool ** board, int rows, int cols);
void editSpace(bool ** board, int rows, int cols);

#endif
