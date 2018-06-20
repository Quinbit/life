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
void displayBoard(bool ** board, int width, int height);
int get_input();
void deinitialize();

#endif
