#include <cstdlib>
#include "UI/mainUI.h"
#include "program/backend.h"
#include <iostream>

using namespace std;

int main() {
  initialize();
  int ch;

  int rows = getrows();
  int cols = getcollumns();

  bool ** board = boardSetup(rows, cols);
  do {
    displayBoard(board, rows, cols);
    ch = getch();

    switch(ch) {
      case KEY_ENTER:
        step(board, rows, cols);
        break;
      case 'e':
        editSpace(board, rows, cols);
        break;
      case KEY_UP:
        move_cursor_up();
        break;
      case KEY_DOWN:
        move_cursor_down();
        break;
      case KEY_RIGHT:
        move_cursor_right();
        break;
      case KEY_LEFT:
        move_cursor_left();
        break;
      case 'r':
        run();
        break;
      case 'l':
        board = loadBoard(NULL);
        break;
      case 's':
        save(board);
        break;
    }
  } while (ch != 'z');

  destroyBoard(board, rows, cols);
  deinitialize();
  return 0;
}
