#include "tictactoe/tictactoe.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace tictactoe {
using std::string;
using namespace std;
Board::Board(string string) { userString = string; }
BoardState Board::EvaluateBoard() {
  if (!isStringConvertible(userString)) {
    throw std::invalid_argument("This string is not convertible.");
  }
  convertToBoard(userString);
  if (!isBoardPlayable(userBoard)) {
    currentEval = BoardState::UnreachableState;
  }
  xWinner(userBoard);
  oWinner(userBoard);
  if (numberOfWinners > 1) {
    currentEval = BoardState::UnreachableState;
  } else if (numberOfWinners == 0) {
    currentEval = BoardState::NoWinner;
  }
  return currentEval;
}
void Board::convertToBoard(string input) {
    int i = 0;
    for(int row = 0; row < boardDimension; row++) {
      for(int column = 0; column < boardDimension; column++) {
        userBoard[row][column] = tolower(input.at(i));
        i++;
      }
    }
  }
bool Board::isStringConvertible(std::string user) {
  for (int character = 0; character < user.length(); character++) {
    user.at(character) = tolower(user.at(character));
  }
  if (user.length() != 9) {
    return false;
  } else if ((user.find('x') == user.npos) && (user.find('o') == user.npos) &&
             (user.find(".") == user.npos)) {
    return false;
  }
  return true;
}
bool Board::isBoardPlayable(char board[3][3]) {
  int countX = countCharOnBoard(board, 'x');
  int countO = countCharOnBoard(board, 'o');
  if (countO > countX) {
    return false;
  } else if (countX > countO + 1) {
    return false;
  }
  return true;
}
int Board::countCharOnBoard(char board[3][3], char player) {
  int count = 0;
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      if (board[row][column] == player) {
        count++;
      }
    }
  }
  return count;
}
void Board::xWinner(char board[3][3]) {
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension - 2; column++) {
      if ('x' == board[row][column] == board[row][column + 1] ==
          board[row][column + 2]) {
        numberOfWinners++;
        currentEval = BoardState::Xwins;
      }
    }
  }
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension - 2; column++) {
      if ('x' == board[row][column] == board[row + 1][column] ==
          board[row + 2][column]) {
        numberOfWinners++;
        currentEval = BoardState::Xwins;
      }
    }
  }
  for (int pos = 0; pos < boardDimension; pos++) {
    if ('x' == board[pos][pos] == board[pos + 1][pos + 1] ==
        board[pos + 2][pos + 2]) {
      numberOfWinners++;
      currentEval = BoardState::Xwins;
    }
  }
  for (int pos = 0; pos < boardDimension; pos++) {
    if ('x' == board[pos][boardDimension - 1] ==
        board[pos + 1][boardDimension - 2] ==
        board[pos + 2][boardDimension - 3]) {
      numberOfWinners++;
      currentEval = BoardState::Xwins;
    }
  }
}
void Board::oWinner(char board[3][3]) {
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension - 2; column++) {
      if ('o' == board[row][column] == board[row][column + 1] ==
          board[row][column + 2]) {
        numberOfWinners++;
        currentEval = BoardState::Owins;
      }
    }
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension - 2; column++) {
      if ('o' == board[row][column] == board[row + 1][column] ==
          board[row + 2][column]) {
        numberOfWinners++;
        currentEval = BoardState::Owins;
      }
    }
  for (int pos = 0; pos < boardDimension; pos++) {
    if ('o' == board[pos][pos] == board[pos + 1][pos + 1] ==
        board[pos + 2][pos + 2]) {
      numberOfWinners++;
      currentEval = BoardState::Owins;
    }
  }
  for (int pos = 0; pos < boardDimension; pos++) {
    if ('o' == board[pos][boardDimension - 1] ==
        board[pos + 1][boardDimension - 2] ==
        board[pos + 2][boardDimension - 3]) {
      numberOfWinners++;
      currentEval = BoardState::Owins;
    }
  }  // namespace tictactoe
}
}