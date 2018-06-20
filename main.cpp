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
  move(1,1);

  do {
    displayBoard(board, rows, cols);
    ch = getch();

    switch(ch) {
      case ' ':
        step(board, rows, cols);
        break;
      case 'e':
        editSpace(board, rows, cols);
        break;
      case KEY_UP:
        move_cursor_up();
        break;
      case KEY_DOWN:
        move_cursor_down(cols);
        break;
      case KEY_RIGHT:
        move_cursor_right(rows);
        break;
      case KEY_LEFT:
        move_cursor_left();
        break;
      case 'r':
        run(board, rows, cols);
        break;
      case 'l':
        loadBoard(board, rows, cols);
        break;
      case 's':
        save(board, rows, cols);
        break;
      case 'c':
        clearBoard(board, rows, cols);
        break;
      case 'n':
        resetBoard(board, rows, cols);
        break;
    }
  } while (ch != 'z');

  destroyBoard(board, rows, cols);
  deinitialize();
  return 0;
}
