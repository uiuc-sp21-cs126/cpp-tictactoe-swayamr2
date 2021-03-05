#pragma once

#include <string>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {

 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(std::string board);

  /**
   * Evaluates the state of the board.
   */

 private:
  std::string userString;
  BoardState currentEval;
  bool boardPlayable = true;
  int boardDimension = 3;
  int numberOfWinners = 0;
  char** userBoard;
  BoardState EvaluateBoard();
  bool isBoardPlayable(char** board);
  int countCharOnBoard(char** board, char player);
  char** convertToBoard(std::string input);
  void xWinner(char** board);
  void oWinner(char** board);
};

}  // namespace tictactoe
