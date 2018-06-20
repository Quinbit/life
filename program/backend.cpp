
#include "backend.h"

using namespace std;

void step(bool ** board, int rows, int cols) {

}

void move_cursor_up() {

}

void move_cursor_down() {

}

void move_cursor_left() {

}

void move_cursor_right() {

}

void editSpace(bool ** board, int rows, int cols) {

}

int getrows() {
  int ch;

  echo();

  do {
    addstr("How many rows would you like: ");
    refresh();
    ch = get_input();
    //addstr("DONE");

    if (ch < 1) {
      clear();
      mvaddstr(0,0,"Invalid input, please try again\n");
      move(1,0);
    }
  } while (ch < 1);

  noecho();
  clear();
  refresh();
  return ch;
}

int getcollumns() {
  int ch;

  echo();
  do {
    addstr("How many collumns would you like: ");
    refresh();
    ch = get_input();
    //addstr("DONE");
    cerr << ch << '\n';

    if (ch < 1) {
      clear();
      mvaddstr(0,0,"Invalid input, please try again\n");
      move(1,0);
      refresh();
    }
  } while (ch < 1);

  noecho();
  clear();
  refresh();
  return ch;
}

bool ** boardSetup(int rows, int cols) {
  int ch = 0;
  int prev = 0;

  echo();

  clear();
  mvaddstr(0,0,"Would you like to randomly initialize the board? (y/N): ");

  while (ch != 10) {
    prev = ch;
    ch = getch();
  }

  ch = prev;

  if (ch == 'y') {
    srand(time(0));
  }

  bool ** b = (bool **)malloc(sizeof(bool *) * cols);

  for (int i=0; i < cols; i++) {
    b[i] = (bool *)malloc(sizeof(bool) * rows);

    for (int x=0; x < rows; x++) {
      b[i][x] = (ch == 'y') * (rand() % 2);
    }
  }

  clear();

  return b;
}

void run() {

}

void save(bool ** board) {

}

bool ** loadBoard(string file) {
  return NULL;
}

void destroyBoard(bool ** board, int rows, int cols) {
  for (int i=0; i < cols; i++) {
    free(board[i]);
  }

  free(board);
}
