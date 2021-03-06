#pragma once

#include <string>
#include <vector>
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
   * Evaluates the state of the board, assigning and returning the correct enum
   * @return currentEval
   */
  BoardState EvaluateBoard();
  std::string userString;
  int boardDimension = 3;
  int numberOfWinners = 0;
  BoardState currentEval;
  char userBoard[3][3];
  /**
   * Checks to see whether the passed string for the Board class is valid
   * @param user
   * @return an invalid argument exception
   */
  bool isStringConvertible(std::string user);

  /**
   * Counts the characters of a certain character(mainly 'X' and 'O') in the string
   * @param board
   * @param player - the passed character into this method
   * @return an integer representing the number of times a character appears
   * on the board
   */
  int countCharOnBoard(char board[3][3], char player);

  bool isBoardPlayable(char board[3][3]);
  /**
   * Converts the passed string into a 2D char array
   * @param input - the initialized string
   */
  void convertToBoard(std::string input);

  /**
   * Method that checks whether the X player has won on the current board
   * @param board
   */
  void xWinner(char board[3][3]);

  /**
   * Method that checks whether the O player has won on the current board
   * @param board
   */
  void oWinner(char board[3][3]);
};

}  // namespace tictactoe
