#pragma once

#include <string>
#include <vector>
namespace tictactoe {
using std::vector;
using std::string;

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

 private:
  string userString;
  int boardDimension = 3;
  BoardState currentEval = BoardState::NoWinner;
  char winningPlayer;
  vector<char> playerMoves;
  vector<vector<char>> gameBoard;

  /**
   * Checks to see whether the passed string for the Board class is valid
   * @param user
   * @return an invalid argument exception
   */
  bool isStringConvertible(string user);

  /**
   * Counts the characters of a certain character(mainly 'X' and 'O') in the string
   * @param board
   * @param player - the passed character into this method
   * @return an integer representing the number of times a character appears
   * on the board
   */
  int countCharOnBoard(vector<vector<char>> userBoard, char player);

  /**
   * Verifies whether a board is playable or not
   * @param userBoard
   */
  bool isBoardPlayable(vector<vector<char>> userBoard);

  /**
   * Converts the passed string into a 2D vector
   * @param input - the initialized string
   */
  void convertToBoard(string input);

  /**
   * Checks whether there is a winner on the current board
   * @param board
   */
  void isWinner(vector<vector<char>> userBoard);

  /**
   * Assigns the correct enum to the holder variable based on who has won and
   * checks for two winners on the board
   * @param player
   */
  void assignAndCheckWinner(char player);

  /**
   * Converts the passed string to lower case to keep regularity
   * @param string
   * @return lower cased string
   */
  string convertToLowerCase(string string);
};

}  // namespace tictactoe
