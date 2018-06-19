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
    cout << ch;

    switch(ch) {
      case KEY_ENTER:
        break;
      case 'E':
        ch = requestPosInt("uhh");
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
      case 'R':
        run();
        break;
      case 'L':
        board = loadBoard(NULL);
        break;
      case 'S':
        save(board);
        break;
    }
  } while (ch != 'z');

  deinitialize();
  return 0;
}
