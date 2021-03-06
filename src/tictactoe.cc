#include "tictactoe/tictactoe.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace tictactoe {
using std::string;
using namespace std;
Board::Board(string string) {
  userString = string;
  if (!isStringConvertible(userString)) {
    throw std::invalid_argument("This string is not convertible.");
  }
}
BoardState Board::EvaluateBoard() {
  convertToBoard(userString);
  if (!isBoardPlayable(userBoard)) {
    currentEval = BoardState::UnreachableState;
    return currentEval;
  }
  isWinner(userBoard);
  return currentEval;
}
void Board::convertToBoard(string input) {
  int character = 0;
  userBoard.resize(0);
  vector<char> playerMoves(0);
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      playerMoves.push_back(tolower(input.at(character)));
      character++;
    }
    userBoard.push_back(playerMoves);
    playerMoves.clear();
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
bool Board::isBoardPlayable(std::vector<std::vector<char>> board) {
  int countX = countCharOnBoard(board, 'x');
  int countO = countCharOnBoard(board, 'o');
  if (countO > countX) {
    return false;
  } else if (countX > countO + 1) {
    return false;
  }
  return true;
}
int Board::countCharOnBoard(std::vector<std::vector<char>> board, char player) {
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
void Board::isWinner(std::vector<std::vector<char>> board) {
  for (int row = 0; row < boardDimension; row++) {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
    {
      winningPlayer = board[row][0];
      assignWinner(winningPlayer);
    }
  }
  for (int column = 0; column < boardDimension; column++) {
    if (board[0][column] == board[1][column] && board[1][column] == board[2][column]) {
      winningPlayer = board[0][column];
      assignWinner(winningPlayer);
    }
  }
for (int pos = 0; pos < 1; pos++) {
  if (board[pos][pos] == board[pos + 1][pos + 1] &&
      board[pos + 1][pos + 1] == board[pos + 2][pos + 2]) {
    winningPlayer = board[pos][pos];
    assignWinner(winningPlayer);
  }
}
for (int pos = 0; pos < 1; pos++) {
  if (board[pos][boardDimension - 1] ==
      board[pos + 1][boardDimension - 2]  &&
      board[pos + 1][boardDimension - 2] == board[pos + 2][boardDimension - 3]) {
    winningPlayer = board[pos][boardDimension - 1];
    assignWinner(winningPlayer);
  }
}
}
void Board::assignWinner(char player) {
  if(player == 'x' && currentEval == BoardState::Owins) {
    currentEval = BoardState::UnreachableState;
  } else if(player == 'o' && currentEval == BoardState::Xwins) {
    currentEval = BoardState::UnreachableState;
  } else if(player == 'x') {
    currentEval = BoardState::Xwins;
  } else if(player == 'o') {
    currentEval = BoardState::Owins;
  }
}
}