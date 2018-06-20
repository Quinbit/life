#ifndef BACKEND_H
#define BACKEND_H

#include <cstdlib>
#include "../UI/mainUI.h"
#include <string>
#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

using namespace std;


void step(bool ** board, int width, int height);
int countNeighbours(bool ** board, int rows, int cols, int x, int y);
int getrows();
int getcollumns();
bool ** boardSetup(int rows, int cols);
void run(bool ** board, int rows, int cols);
void save(bool ** board, int rows, int cols);
void loadBoard(bool ** board, int rows, int cols);
void destroyBoard(bool ** board, int rows, int cols);
void editSpace(bool ** board, int rows, int cols);
void clearBoard(bool ** board, int rows, int cols);
void resetBoard(bool ** board, int rows, int cols);

#endif
