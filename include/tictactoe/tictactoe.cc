#include "tictactoe/tictactoe.h"

#include <list>
#include <stdexcept>
#include <string>
#include <utility>

namespace tictactoe {
using std::string;
using std::initializer_list;
Board::Board(string string) { userString = std::move(string); }
BoardState Board::EvaluateBoard() {
  userBoard = convertToBoard(userString);
  boardPlayable = isBoardPlayable(userBoard);
  if(!boardPlayable) {
    currentEval = BoardState::UnreachableState;
  }
  xWinner(userBoard);
  oWinner(userBoard);
  if(numberOfWinners > 1) {
    currentEval = BoardState::UnreachableState;
  } else if(numberOfWinners == 0) {
    currentEval = BoardState::NoWinner;
  }
  return currentEval;
}
char** Board::convertToBoard(string input) {
  char** board = nullptr;
  int character = 0;
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      board[row][column] = tolower(input.at(character));
      character++;
    }
  }
  return board;
}
bool Board::isBoardPlayable(char** board) {
  int countX = countCharOnBoard(board, 'x');
  int countO = countCharOnBoard(board, 'o');
  if (countO > countX) {
    boardPlayable = false;
  } else if (countX > countO + 1) {
    boardPlayable = false;
  } else if (userString.length() != 9) {
    boardPlayable = false;
  } else {
    for (int row = 0; row < boardDimension; row++) {
      for (int column = 0; column < boardDimension; column++) {
        if (board[row][column] != 'x' && board[row][column] != 'o') {
          boardPlayable = false;
        }
      }
    }
  }
  return boardPlayable;
}

int Board::countCharOnBoard(char** board, char player) {
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
void Board::xWinner(char** board) {
  //Check for row wins
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension; column++) {
      if ('x' == board[row][column] == board[row][column + 1] ==
          board[row][column + 2]) {
        currentEval = BoardState::Xwins;
        numberOfWinners++;
        return;
      }
    }
  //Check for column wins
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension; column++) {
      if ('x' == board[row][column] == board[row + 1][column] ==
          board[row + 2][column]) {
        currentEval = BoardState::Xwins;
        numberOfWinners++;
        return;
      }
    }
  //Check for Left Diagonal wins
  for (int pos = 0; pos < boardDimension; pos++) {
    if('x' == board[pos][pos] == board[pos + 1][pos + 1] ==
        board[pos + 2][pos + 2]) {
        currentEval = BoardState::Xwins;
        numberOfWinners++;
        return;
    }
  }
  //Check for Right Diagonal wins
  for(int pos = 0; pos < boardDimension; pos++) {
    if('x' == board[pos][boardDimension - 1] == board[pos + 1][boardDimension - 2]
      == board[pos + 2][boardDimension - 3]) {
      currentEval = BoardState::Xwins;
      numberOfWinners++;
      return;
    }
  }
}

void Board::oWinner(char** board) {
  //Check for row wins
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension; column++) {
      if ('o' == board[row][column] == board[row][column + 1] ==
          board[row][column + 2]) {
        currentEval = BoardState::Owins;
        numberOfWinners++;
        return;
      }
    }
  //Check for column wins
  for (int row = 0; row < boardDimension; row++)
    for (int column = 0; column < boardDimension; column++) {
      if ('o' == board[row][column] == board[row + 1][column] ==
          board[row + 2][column]) {
        currentEval = BoardState::Owins;
        numberOfWinners++;
        return;
      }
    }
  //Check for Left Diagonal wins
  for (int pos = 0; pos < boardDimension; pos++) {
    if('o' == board[pos][pos] == board[pos + 1][pos + 1] ==
       board[pos + 2][pos + 2]) {
      currentEval = BoardState::Owins;
      numberOfWinners++;
      return;
    }
  }
  //Check for Right Diagonal wins
  for(int pos = 0; pos < boardDimension; pos++) {
    if('o' == board[pos][boardDimension - 1] == board[pos + 1][boardDimension - 2]
       == board[pos + 2][boardDimension - 3]) {
      currentEval = BoardState::Owins;
      numberOfWinners++;
      return;
    }
  }
}
}  // namespace tictactoe
