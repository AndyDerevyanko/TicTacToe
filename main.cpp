#include <iostream>
#include <unistd.h>

using namespace std;

class Board {
public:
  int dim;
  char **arr;
  char *teams;
  int teamsCount;

  void init() {
    arr = new char *[dim];
    for (int i = 0; i < dim; i++) {
      arr[i] = new char[dim];
      for (int j = 0; j < dim; j++)
        arr[i][j] = ' ';
    }

    teams = new char[teamsCount];
    for (int i = 0; i < teamsCount; i++)
      teams[i] = (char)i;
  }

  bool move(int x, int y, char c) {
    c = toupper(c);
    if (x < 0 || x >= dim || y < 0 || y >= dim)
      return false;
    if (arr[x][y] != ' ')
      return false;
    arr[x][y] = c;
    return true;
  }

  bool checkWin(char c) {
    bool winCheck;
    // check horizontals
    for (int i = 0; i < dim; i++) {
      winCheck = true;
      for (int j = 0; j < dim; j++) {
        if (arr[i][j] != c)
          winCheck = false;
      }
      if (winCheck)
        return true;
    }

    // check verticals
    for (int i = 0; i < dim; i++) {
      winCheck = true;
      for (int j = 0; j < dim; j++) {
        if (arr[j][i] != c)
          winCheck = false;
      }
      if (winCheck)
        return true;
    }

    // check diagonals
    winCheck = true;
    for (int i = 0; i < dim; i++) {
      if (arr[i][i] != c)
        winCheck = false;
    }

    if (winCheck)
      return true;

    winCheck = true;
    for (int i = 0; i < dim; i++) {
      if (arr[i][dim - 1 - i] != c)
        winCheck = false;
    }

    if (winCheck)
      return true;

    return false;
  }

  void drawBoard() {
    // all rows but last
    for (int i = 0; i < dim - 1; i++) {
      for (int j = 0; j < dim - 1; j++)
        cout << "     |";
      cout << "     " << endl;

      for (int j = 0; j < dim - 1; j++)
        cout << "  " << arr[j][i] << "  |";
      cout << "  " << arr[dim - 1][i] << "  " << endl;

      for (int j = 0; j < dim - 1; j++)
        cout << "_____|";
      cout << "_____" << endl;
    }

    // last row
    for (int i = 0; i < dim - 1; i++)
      cout << "     |";
    cout << "     " << endl;

    for (int i = 0; i < dim - 1; i++)
      cout << "  " << arr[i][dim - 1] << "  |";
    cout << "  " << arr[dim - 1][dim - 1] << "  " << endl;

    for (int i = 0; i < dim - 1; i++)
      cout << "     |";
    cout << "     " << endl;
  }
};

int main() {

start:
  Board board;
  string input;

  cout << "Welcome to the Customizable Tic-Tac-Toe Game!" << endl;
  cout << "Please enter the boards dimensions: (3 - inf): ";

  while (true) {
    cin >> input;

    try {
      if (stoi(input) > 2) {
        board.dim = stoi(input);
        break;
      } else
        cout << endl << "Invalid input. Please enter a number greater than 2: ";
    } catch (...) {
      cout << endl << "Invalid input. Please enter a number greater than 2: ";
    }
  }

  cout << "Please enter the number of teams playing (1-inf): ";

  while (true) {
    cin >> input;

    try {
      if (stoi(input) > 1) {
        board.teamsCount = stoi(input);
        break;
      } else
        cout << endl << "Invalid input. Please enter a number greater than 1: ";
    } catch (...) {
      cout << endl << "Invalid input. Please enter a number greater than 1: ";
    }
  }

  board.init();

  cout << "Please enter a character to associate with each team: " << endl;
  for (int i = 0; i < board.teamsCount; i++) {
    cout << "Team " << i + 1 << ": ";
    while (true) {
      cin >> input;

      if (input.length() == 1) {
        if (input[0] == ' ')
          cout
              << endl
              << "Invalid input: character cannot be a space. Please reenter: ";
        else {
          for (int j = 0; j < board.teamsCount; j++)
            if (board.teams[i] == toupper(input[0])) {
              cout << "Invalid input: team characters cannot be repeated. "
                      "Please reenter: ";
              continue;
            }
          board.teams[i] = toupper(input[0]);
          break;
        }
      } else
        cout << endl << "Invalid input. Please enter a single character: ";
    }
  }

  cout << "Setup complete, Beginning game..." << endl;
  sleep(3);
  system("clear");

  int moveX;
  int moveY;
  int iteration = 0;
  board.drawBoard();

next:
  cout << "Player \"" << board.teams[iteration]
       << "\", enter the X and Y coordinates of your move: " << endl;
  cout << "X value (1 - " << board.dim << "): ";
  while (true) {
    cin >> input;

    try {
      if (stoi(input) >= 1 && stoi(input) <= board.dim) {
        moveX = stoi(input);
        break;
      } else
        cout << "Invalid input. Please enter a number between 1 and "
             << board.dim << ": ";
    } catch (...) {
      cout << endl
           << "Invalid input. Please enter a number between 1 and " << board.dim
           << ": ";
    }
  }

  cout << "Y value (1 - " << board.dim << "): ";
  while (true) {
    cin >> input;

    try {
      if (stoi(input) >= 1 && stoi(input) <= board.dim) {
        moveY = stoi(input);
        break;
      } else
        cout << "Invalid input. Please enter a number between 1 and "
             << board.dim << ": ";
    } catch (...) {
      cout << endl
           << "Invalid input. Please enter a number between 1 and " << board.dim
           << ": ";
    }
  }

  if (board.move(moveX - 1, moveY - 1, board.teams[iteration])) {
    iteration++;
    if (iteration == board.teamsCount)
      iteration = 0;
    for (int i = 0; i < board.teamsCount; i++) {
      if (board.checkWin(board.teams[i])) {
        cout << "Player \"" << board.teams[i] << "\" wins!" << endl;
        cout << "Restarting game in 5 seconds." << endl;
        sleep(5);
        goto start;
      }
    }
    system("clear");
    board.drawBoard();
    cout << endl << endl;
    goto next;
  } else {
    cout << "Move is Unavailable! Please select another. " << endl;
    goto next;
  }
}
