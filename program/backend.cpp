
#include "backend.h"

using namespace std;

void step(bool ** board, int width, int height) {

}

void move_cursor_up() {

}

void move_cursor_down() {

}

void move_cursor_left() {

}

void move_cursor_right() {

}

int getrows() {
  int ch;

  echo();
  addstr("How many collumns would you like: ");
  refresh();

  do {
    ch = get_input();
    addstr("DONE");

    if (ch < 1) {
      clear();
      mvaddstr(0,0,"Invalid input, please try again\n");
      refresh();
    }
  } while (ch < 1);

  noecho();
  clear();
  refresh();
  return ch;
}

int getcollumns() {
  return 0;
}

bool ** boardSetup(int rows, int cols) {
  return NULL;
}

void run() {

}

void save(bool ** board) {

}

bool ** loadBoard(string file) {
  return NULL;
}
