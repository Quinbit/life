#include "mainUI.h"

void initialize() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

void deinitialize() {
  echo();
  nocbreak();
  endwin();
}

void displayBoard(bool ** board, int rows, int cols) {
  string displayString = " ";
  string symbol = "O";

  for (int i = 0; i < cols; i++) {
    displayString = displayString + "_ ";
  }

  displayString = displayString + "\n";

  for (int i = 0; i < rows; i++) {
    displayString = displayString + "|";
    for (int x = 0; x < cols; x++) {
      if (board[x][i]) {
        displayString = displayString + symbol;
      }
      else {
        displayString = displayString + " ";
      }

      if (x != (cols-1)) {
        displayString = displayString + " ";
      }
      else {
        displayString = displayString + "|\n";
      }
    }
  }

  displayString = displayString + " ";

  for (int i = 0; i < cols; i++) {
    displayString = displayString + "- ";
  }

  displayString = displayString + "\nMove with the arrow keys and press 'e' to edit a cell\nchanging whether it is alive or dead";
  displayString = displayString + "\nPress 's' to save the current board";
  displayString = displayString + "\nPress 'l' to load one of the past boards";
  displayString = displayString + "\nPress 'z' to end the game";

  clear();
  mvaddstr(0,0,displayString.c_str());
  move(1,1);
}

int get_input() {
  char ch;
  string total_string = "";

  do {
    ch = getch();

    if (ch != 10) {
      string str(1, ch);
      total_string = total_string + ch;
      //addstr(str.c_str());
      refresh();
    }
  } while (ch != 10);

  return atoi(total_string.c_str());
}
