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

void displayBoard(bool ** board, int rows, int cols, bool running) {
  string displayString = " ";
  string symbol = "O";
  int x,y;

  getyx(stdscr, y, x);

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
    displayString = displayString + "¯ ";
  }

  if (running) {
    displayString = displayString + "\n ~RUNNING~ \n";
  }

  displayString = displayString + "\nPress 'e' to edit a cell while moving around with the arrow keys\n\tchanging whether it is alive or dead";
  displayString = displayString + "\nPress 's' to save the current board";
  displayString = displayString + "\nPress 'l' to load one of the past boards";
  displayString = displayString + "\nPress 'z' to end the game";
  displayString = displayString + "\nPress 'r' to run the game until you press r again \n\t(press up and down to change run speed)";
  displayString = displayString + "\nPress 'n' to create a new randomly generated board";
  displayString = displayString + "\nPress 'c' to clear the board";
  displayString = displayString + "\nPress SPACE to take a single step";

  clear();
  mvaddstr(0,0,displayString.c_str());
  move(y,x);
  refresh();
}


void displayLoadBoard(bool ** board, int rows, int cols, string name) {
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
    displayString = displayString + "¯ ";
  }

  displayString = displayString + "\n\nThis is file " + name;
  displayString = displayString + "\nPress ENTER to load " + name + " shown above";
  displayString = displayString + "\nPress 'c' to cancel";
  displayString = displayString + "\nPress 'd' to delete the above configuration";

  clear();
  mvaddstr(0,0,displayString.c_str());
  refresh();
}

int get_input() {
  char ch;
  string total_string = "";
  nocbreak();

  do {
    ch = getch();

    if (ch != 10) {
      string str(1, ch);
      total_string = total_string + ch;
      //addstr(str.c_str());
      refresh();
    }
  } while (ch != 10);

  cbreak();

  return atoi(total_string.c_str());
}

string get_name() {
  char ch;
  string total_string = "";
  echo();
  nocbreak();

  clear();
  mvaddstr(0,0,"Please enter in the desired name for this configuration: ");

  do {
    ch = getch();

    if (ch != 10) {
      string str(1, ch);
      total_string = total_string + ch;
      //addstr(str.c_str());
      refresh();
    }
  } while (ch != 10);

  noecho();
  cbreak();

  return total_string;
}

void move_cursor_up() {
  int x;
  int y;

  getyx(stdscr, y, x);
  if (y > 1) {
    y = y - 1;
  }
  move(y, x);
  refresh();
}

void move_cursor_down(int cols) {
  int x;
  int y;

  getyx(stdscr, y, x);
  cerr << x << " " << y << endl;
  if (y < cols) {
    y = y + 1;
  }
  move(y, x);
  refresh();
}

void move_cursor_left() {
  int x;
  int y;

  getyx(stdscr, y, x);
  if (x > 1) {
    x = x - 2;
  }
  move(y, x);
  refresh();
}

void move_cursor_right(int rows) {
  int x;
  int y;

  getyx(stdscr, y, x);
  if (x < 2*rows - 1) {
    x = x + 2;
  }
  move(y, x);
  refresh();
}
