#include "mainUI.h"

void initialize() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

void displayBoard(bool ** board, int rows, int cols) {

}

int requestPosInt(string request) {
  return 0;
}

int get_input() {
  int ch;
  string total_string = "";

  do {
    ch = getch();

    if (ch < 10) {
      total_string = total_string + to_string(ch);
      addstr(to_string(ch).c_str());
      refresh();
    }
  } while (ch != 0);

  return atoi(total_string.c_str());
}
