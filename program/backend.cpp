
#include "backend.h"

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void destroyBoard(bool ** board, int rows, int cols) {
  for (int i=0; i < cols; i++) {
    free(board[i]);
  }

  free(board);
}

bool **createEmptyBoard(int rows, int cols) {
  bool ** b = (bool **)malloc(sizeof(bool *) * cols);

  for (int i=0; i < cols; i++) {
    b[i] = (bool *)malloc(sizeof(bool) * rows);

    for (int x=0; x < rows; x++) {
      b[i][x] = FALSE;
    }
  }

  return b;
}

int countNeighbours(bool ** board, int rows, int cols, int x, int y) {
  int xIndex = 0;
  int yIndex = 0;
  int count = 0;

  for (int i = (x - 1); i <= (x+1); i++) {
    for (int n = (y - 1); n <= (y+1); n++) {
      if (i < 0) {
        xIndex = cols - 1;
      }
      else if (i >= cols) {
        xIndex = 0;
      }
      else {
        xIndex = i;
      }

      if (n < 0) {
        yIndex = rows - 1;
      }
      else if (n >= rows) {
        yIndex = 0;
      }
      else {
        yIndex = n;
      }

      if ((board[xIndex][yIndex]) && ((y != yIndex) || (x != xIndex))) {
        count++;
      }
    }
  }

  return count;
}

void step(bool ** board, int rows, int cols) {
  int count;
  bool b[cols][rows];

  for (int i=0; i < cols; i++) {
    for (int x=0; x < rows; x++) {
      b[i][x] = board[i][x];
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      count = countNeighbours(board, rows, cols, x, i);

      if ((!board[x][i]) && (count == 3)) {
        b[x][i] = TRUE;
      }

      if ((board[x][i]) && (count < 2)) {
        b[x][i] = FALSE;
      }

      if ((board[x][i]) && (count > 3)) {
        b[x][i] = FALSE;
      }
    }
  }

  for (int i=0; i < cols; i++) {
    for (int x=0; x < rows; x++) {
      board[i][x] = b[i][x];
    }
  }
}

void editSpace(bool ** board, int rows, int cols) {
  int x, y;

  getyx(stdscr, y, x);

  x = (x-1) / 2;
  y = y-1;

  board[x][y] = !board[x][y];
  x = x*2 + 1;
  y = y+1;
  move(y,x);
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

  noecho();

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

void run(bool ** board, int rows, int cols) {
  int ch = 0;
  int speed = 100;
  nodelay(stdscr, TRUE);
  while (ch != 'r') {
    ch = getch();
    step(board, rows, cols);
    displayBoard(board, rows, cols, TRUE);

    if (ch == KEY_UP) {
      speed = speed / 1.2;
    }
    else if (ch == KEY_DOWN) {
      speed = speed * 1.2;
    }

    this_thread::sleep_for(chrono::milliseconds(speed));
  }

  nodelay(stdscr, FALSE);
}

void save(bool ** board, int rows, int cols) {
  int x,y;

  getyx(stdscr, y, x);

  string name = get_name();
  ofstream myfile;

  myfile.open("saves/" + name + ".txt");

  myfile << rows << "\n";
  myfile << cols << "\n";

  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
      myfile << board[x][y] << "\n";
    }
  }

  myfile.close();
  clear();
  mvaddstr(0,0,("File " + name + " has been sucessfully saved").c_str());
  refresh();
  this_thread::sleep_for(chrono::seconds(2));

  move(y,x);
}

bool ** loadBoard(bool ** board, int* rows, int* cols) {
  int nrows, ncols;
  int ch = 0;
  string line;
  vector<string> files = vector<string>();
  vector<string>::iterator it;
  ifstream myfile;
  bool ** b;

  clear();

  getdir("saves",files);

  if (files.size() == 2) {
    clear();
    mvaddstr(0,0,"There are currently no saves");
    refresh();
    this_thread::sleep_for(chrono::seconds(2));
    ch = 10;

    b = board;
  }
  else {
    files.erase(remove(files.begin(), files.end(), "."), files.end());
    files.erase(remove(files.begin(), files.end(), ".."), files.end());

    it = files.begin();
  }

  while (ch != 10) {

    myfile.open("saves/" + (*it));

    getline(myfile, line);
    nrows = atoi(line.c_str());
    getline(myfile, line);
    ncols = atoi(line.c_str());

    bool ** nboard = createEmptyBoard(nrows, ncols);

    for (int x = 0; x < ncols; x++) {
      for (int y = 0; y < nrows; y++) {
        getline(myfile, line);
        nboard[x][y] = (bool)atoi(line.c_str());
      }
    }

    myfile.close();

    displayLoadBoard(nboard, nrows, ncols, *it);

    ch = getch();

    switch(ch) {
      case 'c':
        ch = 10;
        b = board;
        destroyBoard(nboard, nrows, ncols);
        break;
      case 10:
        destroyBoard(board, *rows, *cols);
        *rows = nrows;
        *cols = ncols;

        b = createEmptyBoard(nrows, ncols);
        for (int i=0; i < ncols; i++) {
          for (int x=0; x < nrows; x++) {
            b[i][x] = nboard[i][x];
          }
        }
        break;
      case KEY_LEFT:
        if (it == files.begin()) {
          it = files.end();
        }
        it--;
        destroyBoard(nboard, nrows, ncols);
        break;
      case KEY_RIGHT:
        it++;
        if (it==files.end()) {
          it = files.begin();
        }
        destroyBoard(nboard, nrows, ncols);
        break;
      case 'd':
        if(remove(("saves/" + (*it)).c_str()) != 0 ) {
          clear();
          mvaddstr(0,0,"Could not delete file");
          refresh();
          this_thread::sleep_for(chrono::seconds(2));
        }
        else {
          clear();
          mvaddstr(0,0,"Deleted File");
          refresh();
          this_thread::sleep_for(chrono::seconds(2));
          files.erase(remove(files.begin(), files.end(), *it), files.end());

          if (files.size() == 0) {
            clear();
            mvaddstr(0,0,"There are currently no saves");
            refresh();
            this_thread::sleep_for(chrono::seconds(2));
            ch = 10;

            b = board;
          }
        }
        break;
    }
  }

  move(1,1);
  return b;
}


void clearBoard(bool ** board, int rows, int cols) {
  for (int i=0; i < cols; i++) {
    for (int x=0; x < rows; x++) {
      board[i][x] = FALSE;
    }
  }
}

void resetBoard(bool ** board, int rows, int cols) {
  srand(time(0));
  for (int i=0; i < cols; i++) {
    for (int x=0; x < rows; x++) {
      board[i][x] = rand() % 2;
    }
  }
}
