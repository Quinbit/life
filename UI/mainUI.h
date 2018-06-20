#ifndef MAINUI_H
#define MAINUI_H

#include <curses.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include <iostream>

using namespace std;

void initialize();
void displayBoard(bool ** board, int rows, int cols, bool running=FALSE);
int get_input();
void deinitialize();
void move_cursor_up();
void move_cursor_down(int cols);
void move_cursor_left();
void move_cursor_right(int rows);
void displayNeighbour(bool ** board, int rows, int cols);
int countNeighbours(bool ** board, int rows, int cols, int x, int y);
string get_name();
void displayLoadBoard(bool ** nboard, int nrows, int ncols, string name);

#endif
