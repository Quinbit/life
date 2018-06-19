#ifndef MAINUI_H
#define MAINUI_H

#include <curses.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctype.h>

using namespace std;

void initialize();
void displayBoard(bool ** board, int width, int height);
int requestPosInt(string request);
int get_input();

#endif
