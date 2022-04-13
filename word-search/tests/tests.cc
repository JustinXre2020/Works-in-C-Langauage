// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Findword checks 1", "case1") {
    // Special case for non-square
    std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 'u'},
                                          {'t', 'e', 'l', 'n', 'o'},
                                          {'h', 'e', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);  

    //do not exist
    REQUIRE(wss.FindWord("cta").word == "");
    REQUIRE(wss.FindWord("cta").char_positions.size() == 0);
    REQUIRE(wss.FindWord("chaoa").word == "");
    REQUIRE(wss.FindWord("chaoa").char_positions.size() == 0);
    REQUIRE(wss.FindWord("cee").word == "");
    REQUIRE(wss.FindWord("cee").char_positions.size() == 0);
    REQUIRE(wss.FindWord("une").word == "");
    REQUIRE(wss.FindWord("une").char_positions.size() == 0);

    // exist in the puzzle
    REQUIRE(wss.FindWord("cth").word == "cth");
    REQUIRE(wss.FindWord("chaou").word == "chaou");
    REQUIRE(wss.FindWord("cel").word == "cel");
    REQUIRE(wss.FindWord("unl").word == "unl");
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Findword checks 2", "case2") {
    std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 'u'},
                                          {'t', 'e', 'l', 'n', 'o'},
                                          {'a', 'h', 'i', 'o', 'm'},
                                          {'c', 't', 'a', 'h', 'u'},
                                          {'y', 'e', 'l', 't', 'a'}};
    WordSearchSolver wss(puzzle);
    // WordLocation w = {"hello", std::vector<CharPositions>{ {'h', 2, 0}, {'e', 2, 1}, {'l', 2, 2}, {'l', 2, 3}, {'o', 2, 4} } };
    WordLocation ans = wss.FindWord("catho");
    REQUIRE(ans.word == "");
    REQUIRE(wss.FindWord("catho", CheckDirection::kHorizontal).char_positions.size() == 0);
    REQUIRE(wss.FindWord("catho", CheckDirection::kLeftDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("catho", CheckDirection::kRightDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("catho", CheckDirection::kVertical).char_positions.size() == 0);
    REQUIRE(wss.FindWord("catho").char_positions.size() == 0);
   

    WordLocation w = {"unity", std::vector<CharPositions>{ {'u', 0, 4}, {'n', 1, 3}, {'i', 2, 2}, {'t', 3, 1}, {'y', 4, 0} } };
    WordLocation ans2 = wss.FindWord("unity");
    REQUIRE(ans2.word == w.word);
    REQUIRE(wss.FindWord("unity", CheckDirection::kHorizontal).char_positions.size() == 0);
    REQUIRE(wss.FindWord("unity", CheckDirection::kLeftDiag).word == "unity");
    REQUIRE(wss.FindWord("unity", CheckDirection::kRightDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("unity", CheckDirection::kVertical).char_positions.size() == 0);
    REQUIRE(wss.FindWord("unity").char_positions.size() == 5);
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        REQUIRE(ans2.char_positions[i].character == w.char_positions[i].character);
        REQUIRE(ans2.char_positions[i].row == w.char_positions[i].row);
        REQUIRE(ans2.char_positions[i].col == w.char_positions[i].col);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////




TEST_CASE("Findword checks 3", "case3") {
    std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 'u'},
                                          {'t', 'e', 'l', 'n', 'o'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 't', 'a', 'h', 'u'},
                                          {'y', 'e', 'l', 't', 'a'}};
    WordSearchSolver wss(puzzle);
    WordLocation w = {"hello", std::vector<CharPositions>{ {'h', 2, 0}, {'e', 2, 1}, {'l', 2, 2}, {'l', 2, 3}, {'o', 2, 4} } };
    WordLocation ans = wss.FindWord("hello");
    REQUIRE(ans.word == w.word);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word == "hello");
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).char_positions.size() == 0);
    REQUIRE(wss.FindWord("hello").char_positions.size() == 5);
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        REQUIRE(ans.char_positions[i].character == w.char_positions[i].character);
        REQUIRE(ans.char_positions[i].row == w.char_positions[i].row);
        REQUIRE(ans.char_positions[i].col == w.char_positions[i].col);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Findword checks 4", "case4") {
    std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 'u'},
                                          {'t', 'e', 'l', 'n', 'o'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 't', 'a', 'h', 'u'},
                                          {'y', 'e', 'l', 't', 'a'}};
    WordSearchSolver wss(puzzle);  

    WordLocation w = {"onlht", std::vector<CharPositions>{ {'o', 0, 3}, {'n', 1, 3}, {'l', 2, 3}, {'h', 3, 3}, {'t', 4, 3} } };
    WordLocation ans = wss.FindWord("onlht");
    REQUIRE(ans.word == w.word);
    REQUIRE(wss.FindWord("onlht", CheckDirection::kHorizontal).char_positions.size() == 0);
    REQUIRE(wss.FindWord("onlht", CheckDirection::kLeftDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("onlht", CheckDirection::kRightDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("onlht", CheckDirection::kVertical).word == "onlht");
    REQUIRE(wss.FindWord("onlht").char_positions.size() == 5);
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        REQUIRE(ans.char_positions[i].character == w.char_positions[i].character);
        REQUIRE(ans.char_positions[i].row == w.char_positions[i].row);
        REQUIRE(ans.char_positions[i].col == w.char_positions[i].col);
    }

    WordLocation w2 = {"celha", std::vector<CharPositions>{ {'c', 0, 0}, {'e', 1, 1}, {'l', 2, 2}, {'h', 3, 3}, {'a', 4, 4} } };
    WordLocation ans2 = wss.FindWord("celha");
    REQUIRE(ans2.word == w2.word);
    REQUIRE(wss.FindWord("celha", CheckDirection::kHorizontal).char_positions.size() == 0);
    REQUIRE(wss.FindWord("celha", CheckDirection::kLeftDiag).char_positions.size() == 0);
    REQUIRE(wss.FindWord("celha", CheckDirection::kRightDiag).word == "celha");
    REQUIRE(wss.FindWord("celha", CheckDirection::kVertical).char_positions.size() == 0);
    REQUIRE(wss.FindWord("celha").char_positions.size() == 5);
    for (size_t i = 0; i < w2.char_positions.size(); ++i) {
        REQUIRE(ans2.char_positions[i].character == w2.char_positions[i].character);
        REQUIRE(ans2.char_positions[i].row == w2.char_positions[i].row);
        REQUIRE(ans2.char_positions[i].col == w2.char_positions[i].col);
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////


TEST_CASE("Findword checks 5", "case5") {
    std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 'u'},
                                          {'t', 'e', 'l', 'n', 'o'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 't', 'a', 'h', 'u'},
                                          {'y', 'e', 'l', 't', 'a'}};
    WordSearchSolver wss(puzzle);  

    //do not exist
    REQUIRE(wss.FindWord("cthca").word == "");
    REQUIRE(wss.FindWord("cthca").char_positions.size() == 0);
    REQUIRE(wss.FindWord("chaoa").word == "");
    REQUIRE(wss.FindWord("chaoa").char_positions.size() == 0);
    REQUIRE(wss.FindWord("cela").word == "");
    REQUIRE(wss.FindWord("cela").char_positions.size() == 0);
    REQUIRE(wss.FindWord("unly").word == "");
    REQUIRE(wss.FindWord("unly").char_positions.size() == 0);

    // exist in the puzzle
    REQUIRE(wss.FindWord("cthcy").word == "cthcy");
    REQUIRE(wss.FindWord("chaou").word == "chaou");
    REQUIRE(wss.FindWord("celh").word == "celh");
    REQUIRE(wss.FindWord("unlt").word == "unlt");
}