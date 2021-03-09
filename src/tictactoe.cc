#include "tictactoe/tictactoe.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace tictactoe {
using std::string;
using std::vector;
using std::invalid_argument;
using std::move;
Board::Board(string string) {
  userString = convertToLowerCase(move(string));
  /*
   * If the string is convertible, we convert it into a game board. Else, throw
   * an invalid argument exception
   */
  if (!isStringConvertible(userString)) {
    throw invalid_argument("This string is not convertible.");
  } else {
    convertToBoard(userString);
  }
}
BoardState Board::EvaluateBoard() {
  //Check if the board can be played on or not
  if(!isBoardPlayable(gameBoard)) {
    currentEval = BoardState::UnreachableState;
    return currentEval;
  }
  //Check for a winner & assign the correct enum
  isWinner(gameBoard);
  return currentEval;
}
void Board::convertToBoard(string input) {
  int character = 0;
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      //Store the moves into the inner vector
      playerMoves.push_back(tolower(input.at(character)));
      character++;
    }
    //Push the inner vector into the outer vector and clear the inner vector
    gameBoard.push_back(playerMoves);
    playerMoves.clear();
  }
}
bool Board::isStringConvertible(string moves) {
  //If the string cannot be converted to a 3x3 square, it is not convertible
  if (moves.length() != (boardDimension * boardDimension)) {
    return false;
  }
  return true;
}
bool Board::isBoardPlayable(vector<vector<char>> board) {
  int countX = countCharOnBoard(board, 'x');
  int countO = countCharOnBoard(board, 'o');
  // If O's are greater than X's on the board, the board is not valid
  if (countO > countX) {
    return false;
    // If X's are much greater than O's on the board, someone has cheated
  } else if (countX > countO + 1) {
    return false;
  }
  return true;
}
int Board::countCharOnBoard(vector<vector<char>> board, char player) {
  int charCount = 0;
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      if (board[row][column] == player) {
        charCount++;
      }
    }
  }
  return charCount;
}
void Board::isWinner(vector<vector<char>> board) {
  //Loop through the rows of the outer vector
  for (int row = 0; row < boardDimension; row++) {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
      //Set the winning player to the certain character
      winningPlayer = board[row][0];
      //Run the winning player through a check for two winners
      assignAndCheckWinner(winningPlayer);
    }
  }
  //Loops through the columns of the outer vector
  for (int column = 0; column < boardDimension; column++) {
    if (board[0][column] == board[1][column] &&
        board[1][column] == board[2][column]) {
      winningPlayer = board[0][column];
      assignAndCheckWinner(winningPlayer);
    }
  }
  //Loops through the left diagonals of the outer vector
  for (int pos = 0; pos < 1; pos++) {
    if (board[pos][pos] == board[pos + 1][pos + 1] &&
        board[pos + 1][pos + 1] == board[pos + 2][pos + 2]) {
      winningPlayer = board[pos][pos];
      assignAndCheckWinner(winningPlayer);
    }
  }
  //Loops through the right diagonals of the outer vector
  for (int pos = 0; pos < 1; pos++) {
    if (board[pos][boardDimension - 1] == board[pos + 1][boardDimension - 2] &&
        board[pos + 1][boardDimension - 2] ==
            board[pos + 2][boardDimension - 3]) {
      winningPlayer = board[pos][boardDimension - 1];
      assignAndCheckWinner(winningPlayer);
    }
  }
}
void Board::assignAndCheckWinner(char player) {
  switch (player) {
    case 'x':
      //If the winning state has already been set, there must be 2 winners
      if (currentEval == BoardState::Owins) {
        currentEval = BoardState::UnreachableState;
        break;
      } else {
        currentEval = BoardState::Xwins;
        break;
      }
    case 'o':
      if (currentEval == BoardState::Xwins) {
        currentEval = BoardState::UnreachableState;
        break;
      } else {
        currentEval = BoardState::Owins;
        break;
      }
  }
}
string Board::convertToLowerCase(string string)  {
  for (char character : string) {
    tolower(character);
  }
    return string;
  }
}
