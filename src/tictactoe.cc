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
  userString = move(string);
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
  if (!isBoardPlayable(gameBoard)) {
    currentEval = BoardState::UnreachableState;
    return currentEval;
  }
  //Check for a winner & assign the correct enum
  isWinner(gameBoard);
  return currentEval;
}
void Board::convertToBoard(string input) {
  int character = 0;
  //Reset the sizes of both the outer and inner vectors to 0
  gameBoard.resize(0);
  playerMoves.resize(0);
  for (int row = 0; row < boardDimension; row++) {
    for (int column = 0; column < boardDimension; column++) {
      //Store the moves into the inner vector
      playerMoves.push_back(tolower(input.at(character)));
      character++;
    }
    //Push the inner vector into the outer vector
    gameBoard.push_back(playerMoves);
    playerMoves.clear();
  }
}
bool Board::isStringConvertible(string user) {
  for (char & character : user) {
    character = tolower(character);
  }
  if (user.length() != (boardDimension * boardDimension)) {
    return false;
  //If the string contains special characters, it is not convertible
  } else if ((user.find('x') == user.npos) && (user.find('o') == user.npos) &&
             (user.find(".") == user.npos)) {
    return false;
  }
  return true;
}
bool Board::isBoardPlayable(vector<vector<char>> board) {
  int countX = countCharOnBoard(board, 'x');
  int countO = countCharOnBoard(board, 'o');
  //If O's are greater than X's on the board, the board is not valid
  if (countO > countX) {
    return false;
  //If X's are much greater than O's on the board, someone has cheated
  } else if (countX > countO + 1) {
    return false;
  }
  return true;
}
int Board::countCharOnBoard(vector<vector<char>> board, char player) {
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
void Board::isWinner(vector<vector<char>> board) {
  //Loop through the rows of the outer vector
  for (int row = 0; row < boardDimension; row++) {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
    {
      //Set the winning player to the certain character
      winningPlayer = board[row][0];
      assignWinner(winningPlayer);
    }
  }
  //Loops through the columns of the outer vector
  for (int column = 0; column < boardDimension; column++) {
    if (board[0][column] == board[1][column] && board[1][column] == board[2][column]) {
      winningPlayer = board[0][column];
      assignWinner(winningPlayer);
    }
  }
  //Loops through the left diagonals of the outer vector
  for (int pos = 0; pos < 1; pos++) {
    if (board[pos][pos] == board[pos + 1][pos + 1] &&
        board[pos + 1][pos + 1] == board[pos + 2][pos + 2]) {
      winningPlayer = board[pos][pos];
      assignWinner(winningPlayer);
  }
}
  //Loops through the right diagonals of the outer vector
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
  /*
   * If the current state of the game differs from the state of the winning player,
   * set the board state to be unreachable, as there must be two winners
   * */
  if(player == 'x' && currentEval == BoardState::Owins) {
    currentEval = BoardState::UnreachableState;
  } else if (player == 'o' && currentEval == BoardState::Xwins) {
    currentEval = BoardState::UnreachableState;
  //If no two winners are found, set the board state to the proper player
  } else if (player == 'x') {
    currentEval = BoardState::Xwins;
  } else if (player == 'o') {
    currentEval = BoardState::Owins;
  }
}
}