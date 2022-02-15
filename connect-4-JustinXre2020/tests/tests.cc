// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "board.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  // REQUIRE(AreEqual(solution, student.board));

/////////////////////////////////////////////////////////////////////////////////////////////

  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // DropDiskToBoard(student, DiskType::kPlayer1, 2);
  // std::cout << BoardToStr(student);

/////////////////////////////////////////////////////////////////////////////////////////////

  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  std::cout << BoardToStr(student) << std::endl;
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

/////////////////////////////////////////////////////////////////////////////////////////////
  Board student1;  // NOLINT
  InitBoard(student1);
  // REQUIRE(AreEqual(solution, student1.board));

/////////////////////////////////////////////////////////////////////////////////////////////
  REQUIRE(BoardLocationInBounds(-1, 7) == false);
  REQUIRE(BoardLocationInBounds(1, 1) == true);
  REQUIRE(BoardLocationInBounds(0, 0) == true);
  REQUIRE(BoardLocationInBounds(6, 7) == false);
  DropDiskToBoard(student1, DiskType::kPlayer1, 2);
  DropDiskToBoard(student1, DiskType::kPlayer2, 5);
  DropDiskToBoard(student1, DiskType::kPlayer1, 2);
  DropDiskToBoard(student1, DiskType::kPlayer2, 3);
  DropDiskToBoard(student1, DiskType::kPlayer1, 2);
  DropDiskToBoard(student1, DiskType::kPlayer2, 3);
  DropDiskToBoard(student1, DiskType::kPlayer1, 2);
  std::cout << BoardToStr(student1) << std::endl;
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  REQUIRE(CheckForWinner(student1, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student1, DiskType::kPlayer2) == false);


/////////////////////////////////////////////////////////////////////////////////////////////

  Board student2;  // NOLINT
  InitBoard(student2);
  // REQUIRE(AreEqual(solution, student2.board));


/////////////////////////////////////////////////////////////////////////////////////////////

  DropDiskToBoard(student2, DiskType::kPlayer1, 2);
  DropDiskToBoard(student2, DiskType::kPlayer2, 3);
  DropDiskToBoard(student2, DiskType::kPlayer1, 3);
  DropDiskToBoard(student2, DiskType::kPlayer2, 4);
  DropDiskToBoard(student2, DiskType::kPlayer2, 4);
  DropDiskToBoard(student2, DiskType::kPlayer1, 4);
  DropDiskToBoard(student2, DiskType::kPlayer2, 5);
  DropDiskToBoard(student2, DiskType::kPlayer2, 5);
  DropDiskToBoard(student2, DiskType::kPlayer2, 5);
  DropDiskToBoard(student2, DiskType::kPlayer1, 5);
  std::cout << BoardToStr(student2) << std::endl;
  REQUIRE(CheckForWinner(student2, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student2, DiskType::kPlayer2) == false);

/////////////////////////////////////////////////////////////////////////////////////////////

  Board student3;  // NOLINT
  InitBoard(student3);
  // REQUIRE(AreEqual(solution, student3.board));


/////////////////////////////////////////////////////////////////////////////////////////////

  DropDiskToBoard(student3, DiskType::kPlayer1, 6);
  DropDiskToBoard(student3, DiskType::kPlayer2, 5);
  DropDiskToBoard(student3, DiskType::kPlayer1, 5);
  DropDiskToBoard(student3, DiskType::kPlayer2, 4);
  DropDiskToBoard(student3, DiskType::kPlayer2, 4);
  DropDiskToBoard(student3, DiskType::kPlayer1, 4);
  DropDiskToBoard(student3, DiskType::kPlayer2, 3);
  DropDiskToBoard(student3, DiskType::kPlayer2, 3);
  DropDiskToBoard(student3, DiskType::kPlayer2, 3);
  DropDiskToBoard(student3, DiskType::kPlayer1, 3);
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  std::cout << BoardToStr(student3) << std::endl;
  REQUIRE(CheckForWinner(student3, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student3, DiskType::kPlayer2) == false);

/////////////////////////////////////////////////////////////////////////////////////////////


  Board student4;  // NOLINT
  InitBoard(student4);

  for (unsigned i = 0; i < 6; ++i) {
    for (unsigned j = 0; j < 7; ++j) {
      DropDiskToBoard(student4, solution[i][j], j);
    }
  }
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  std::cout << BoardToStr(student4) << std::endl;
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student4, DiskType::kPlayer1) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer2, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student4, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student4, DiskType::kPlayer2) == false);


/////////////////////////////////////////////////////////////////////////////////////////////

  DiskType solution2[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1} 
  };
  Board student5;  // NOLINT
  InitBoard(student5);

  for (unsigned i = 0; i < 6; ++i) {
    for (unsigned j = 0; j < 7; ++j) {
      DropDiskToBoard(student5, solution2[i][j], j);
    }
  }
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  std::cout << BoardToStr(student5) << std::endl;
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer1, WinningDirection::kRightDiag) == true);
  REQUIRE(CheckForWinner(student5, DiskType::kPlayer1) == true);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer2, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student5, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student5, DiskType::kPlayer2) == false);

/////////////////////////////////////////////////////////////////////////////////////////////

    DiskType solution3[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2} 
  };

  Board student6;  // NOLINT
  InitBoard(student6);

  for (unsigned i = 0; i < 6; ++i) {
    for (unsigned j = 0; j < 7; ++j) {
      DropDiskToBoard(student6, solution3[i][j], j);
    }
  }
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  std::cout << BoardToStr(student6) << std::endl;
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student6, DiskType::kPlayer1) == false);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer2, WinningDirection::kHorizontal) == true);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer2, WinningDirection::kVertical) == true);
  REQUIRE(SearchForWinner(student6, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student6, DiskType::kPlayer2) == true);

/////////////////////////////////////////////////////////////////////////////////////////////

    DiskType solution4[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2} 
  };

  Board student7;  // NOLINT
  InitBoard(student7);

  for (unsigned i = 0; i < 6; ++i) {
    for (unsigned j = 0; j < 7; ++j) {
      DropDiskToBoard(student7, solution4[i][j], j);
    }
  }
  std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
  std::cout << BoardToStr(student7) << std::endl;
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student7, DiskType::kPlayer1) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer2, WinningDirection::kHorizontal) == true);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student7, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student7, DiskType::kPlayer2) == true);
}
TEST_CASE("BoardLocationinBounds2", "[board_drop_col]") {
  Board b;
  InitBoard(b);
  bool t = false;
  try
  {
    DropDiskToBoard(b, DiskType::kPlayer2, 8);
  }
  catch(std::runtime_error e)
  {
    t = true;
  }
  REQUIRE(t == true);
}

TEST_CASE("BoardLocationinBounds3", "[board_drop_row]") {
  Board b;
  InitBoard(b);
  bool t = false;
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  try
  {
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
  }
  catch(std::runtime_error e)
  {
    t = true;
  }
  REQUIRE(t == true);
}

TEST_CASE("BoardLocationinBounds4", "[board_drop_incomplete]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2) == false);
}

TEST_CASE("BoardLocationinBounds5", "[board_drop_out_of_bound]") {
  Board b;
  InitBoard(b);
  bool t = false;
  try
  {
    DropDiskToBoard(b, DiskType::kPlayer2, -1);
  }
  catch(std::runtime_error e)
  {
    t = true;
  }
  REQUIRE(t == true);
}
