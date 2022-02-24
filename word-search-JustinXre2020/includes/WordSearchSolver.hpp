#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
 public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
    puzzle_ = puzzle;
    puzzle_height_ = puzzle.size();
    puzzle_width_ = puzzle[0].size();
  }
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

 private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<CharPositions> HelperRight(const std::string& word);
  std::vector<CharPositions> HelperLeft(const std::string& word);
  std::vector<CharPositions> HelperVertical(const std::string& word);
  std::vector<CharPositions> HelperHorizontal(const std::string& word);
  void AddHori(std::string& str, std::vector<CharPositions>& vec, size_t row, size_t col, const std::string& w, bool b);
  void AddVec(std::string& str, std::vector<CharPositions>& vec, size_t row, size_t col, const std::string& w, bool b);
  void AddRight(std::string& str, std::vector<CharPositions>& vec, size_t row, size_t col, const std::string& w, bool b);
  void AddLeft(std::string& str, std::vector<CharPositions>& vec, size_t row, size_t col, const std::string& w, bool b);
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif