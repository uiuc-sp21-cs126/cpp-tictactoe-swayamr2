#include <string>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>
using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("XOXO"), std::invalid_argument);
  }
  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("XOXOXOXOXOXOX"), std::invalid_argument);
  }
  SECTION("Empty string") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }
}
TEST_CASE("Invalid playing board") {
  SECTION("Too many X's") {
    REQUIRE(Board("XXXOOOXXX").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Too many O's") {
    REQUIRE(Board("OXOXOXOXO").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Board with all X's") {
    REQUIRE(Board("XXXXXXXXX").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Board with all O's") {
    REQUIRE(Board("OOOOOOOOO").EvaluateBoard() == BoardState::UnreachableState);
  }
}
TEST_CASE("Board where X Wins via Row") {
  SECTION("1st Row X Win") {
    REQUIRE(Board("XXX.O.O..").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("2nd Row X Win") {
    REQUIRE(Board("...XXXO.O").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("3rd Row X Win") {
    REQUIRE(Board("..OOXOXXX").EvaluateBoard() == BoardState::Xwins);
  }
}
TEST_CASE("Board where X Wins via Column") {
  SECTION("1st Column X Win") {
    REQUIRE(Board("XOXX..XOO").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("2nd Column X Win") {
    REQUIRE(Board("OX..X..XO").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("3rd Column X Win") {
    REQUIRE(Board("..XOXXOOX").EvaluateBoard() == BoardState::Xwins);
  }
}
TEST_CASE("Board where O Wins via Row") {
  SECTION("1st Row O Win") {
    REQUIRE(Board("OOO.XX.XX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("2nd Row O Win") {
    REQUIRE(Board("..XOOO.XX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("3rd Row O Win") {
    REQUIRE(Board(".XX.X.OOO").EvaluateBoard() == BoardState::Owins);
  }
}
TEST_CASE("Board where O Wins via Column") {
  SECTION("1st Column O Win") {
    REQUIRE(Board("OXXOO.OXX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("2nd Column O Win") {
    REQUIRE(Board(".O..OXXOX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("3rd Column O Win") {
    REQUIRE(Board("..OXXO.XO").EvaluateBoard() == BoardState::Owins);
  }
}
TEST_CASE("Board where X Wins via Diagonal") {
  SECTION("Left-to-right Diagonal X Win") {
    REQUIRE(Board("XOOXXOOXX").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Right-to-left Diagonal X Win") {
    REQUIRE(Board("..XOXOX..").EvaluateBoard() == BoardState::Xwins);
  }
}
TEST_CASE("Board where O Wins via Diagonal") {
  SECTION("Left-to-right Diagonal O Win") {
    REQUIRE(Board("OXX.OX..O").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Right-to-left Diagonal O Win") {
    REQUIRE(Board("..O.OXOXX").EvaluateBoard() == BoardState::Owins);
  }
}
TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("XXOOOXXXO").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Partly-filled board with last O move") {
    REQUIRE(Board("XX...OO..").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Party-filled Board with last X move") {
    REQUIRE(Board("XX.O..X.O").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Empty Board with no winner") {
    REQUIRE(Board(".........").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Board has 2 winners") {
  SECTION("Board with 2 Row wins") {
    REQUIRE(Board("XXXOOO...").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Board with 2 Column wins") {
    REQUIRE(Board("XO.XO.XO.").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Board with 2 X wins") {
    REQUIRE(Board("XXXXOOXOO").EvaluateBoard() == BoardState::Xwins);
  }
}
TEST_CASE("Board with special characters") {
  SECTION("Special Board with X win") {
    REQUIRE(Board("^%@XXXO*O").EvaluateBoard() == BoardState::Xwins);
 }
  SECTION("Special Board with O win") {
    REQUIRE(Board("&O]!OXXOX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Special Board with no winner") {
    REQUIRE(Board("X&)#*)O#?").EvaluateBoard() == BoardState::NoWinner);
  }
}
