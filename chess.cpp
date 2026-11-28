#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const string cReset = "\033[0m";
const string cBlackBG = "\033[48;5;94m";
const string cWhiteBG = "\033[48;5;180m";
const string cBlackPiece = "\033[30m";
const string cWhitePiece = "\033[37m";

struct Piece {
  bool isWhite;
  char type;
};

struct Field {
  bool isWhite;
  Piece piece;
};

void drawBoard(vector<vector<Field>> board) {

  system("clear");

  cout << "  a  b  c  d  e  f  g  h" << endl;

  for(int line = 0; line < board.size(); line++) {
    cout << line << " ";
    for(int column = 0; column < board[0].size(); column++) {

      // bg color
      if(board[line][column].isWhite) {
        cout << cWhiteBG;
      }
      else {
        cout << cBlackBG;
      }

      // piece color
      if(board[line][column].piece.isWhite) {
        cout << cWhitePiece;
      }
      else {
        cout << cBlackPiece;
      }

      // piece
      cout << " ";
      switch (board[line][column].piece.type)
      {
        case 'k': cout << "♚\uFE0E"; break;
        case 'q': cout << "♛\uFE0E"; break;
        case 'r': cout << "♜\uFE0E"; break;
        case 'b': cout << "♝\uFE0E"; break;
        case 'n': cout << "♞\uFE0E"; break;
        case 'p': cout << "♟\uFE0E"; break;
      
      default:
        cout << " ";
        break;
      }
      cout << " " << cReset;

    }
    cout << " " << line;

    if(line == 0) {
      cout << "\tHistory:";
    }
    if(line > 0) {
      cout << "\t...";
    }
    cout << endl;
  }

  cout << "   a  b  c  d  e  f  g  h" << endl;
}

vector<vector<Field>> generateBoard() {

  Field field;
  Piece piece;

  string color;
  int count = 1;

  vector<vector<Field>> board;

  // create chess board and fill it with Fields
  // including piece and field information
  for (int line = 0; line < 8; line++) {

    board.push_back(vector<Field>{});

    if (line % 2 == 0) {
      field.isWhite = true;
    } 
    else {
      field.isWhite = false;
    }

    for (int column = 0; column < 8; column++) {

      board[line].push_back(field);

      if (field.isWhite == true) {
        field.isWhite = false;
      }
      else {field.isWhite = true;}

      count++;
    }
  }

  return board;
}

int main() {
  drawBoard(generateBoard());
  return 0;
}
