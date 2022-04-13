#include "WordSearchSolver.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "WordLocation.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (!FindWord(word, CheckDirection::kHorizontal).word.empty()) {
    return FindWord(word, CheckDirection::kHorizontal);
  } else if (!FindWord(word, CheckDirection::kVertical).word.empty()) {
    return FindWord(word, CheckDirection::kVertical);
  } else if (!FindWord(word, CheckDirection::kLeftDiag).word.empty()) {
    return FindWord(word, CheckDirection::kLeftDiag);
  }
  return FindWord(word, CheckDirection::kRightDiag);
}

void WordSearchSolver::AddRight(std::string& str,
                                std::vector<CharPositions>& vec, size_t row,
                                size_t col, const std::string& w, bool b) {
  if (b) {  // Add char with row going up, col going up
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row + a][col + a];
      CharPositions ch = {puzzle_[row + a][col + a], row + a, col + a};
      vec.push_back(ch);
    }
  } else {  // Add char with row going down, col going down
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row - a][col - a];
      CharPositions ch = {puzzle_[row - a][col - a], row - a, col - a};
      vec.push_back(ch);
    }
  }
}

std::vector<CharPositions> WordSearchSolver::HelperRight(
    const std::string& word) {
  std::vector<CharPositions> v;
  for (size_t i = 0; i < puzzle_height_; ++i) {
    std::string s;
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (word[0] == puzzle_[i][j]) {
        if (LocationInBounds(
                i + word.length() - 1,
                j + word.length() - 1) &&  // If both direction are inbound
            LocationInBounds(i - word.length() + 1, j - word.length() + 1)) {
          AddRight(s, v, i, j, word, true);  // Try both direction, return if
                                             // one matches the input word
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
          AddRight(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(
                       i + word.length() - 1,  // Row going down, col going down
                       j + word.length() - 1) &&
                   LocationInBounds(i - word.length() + 1,
                                    j - word.length() + 1)) {
          AddRight(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(
                       i - word.length() + 1,  // Row going up, col going up
                       j - word.length() + 1) &&
                   LocationInBounds(i + word.length() - 1,
                                    j + word.length() - 1)) {
          AddRight(s, v, i, j, word, true);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        }
      }
    }
  }
  return v;
}

void WordSearchSolver::AddLeft(std::string& str,
                               std::vector<CharPositions>& vec, size_t row,
                               size_t col, const std::string& w, bool b) {
  if (b) {  // Add char with row going up, col going down
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row + a][col - a];
      CharPositions ch = {puzzle_[row + a][col - a], row + a, col - a};
      vec.push_back(ch);
    }
  } else {  // Add char with row going down, col going up
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row - a][col + a];
      CharPositions ch = {puzzle_[row - a][col + a], row - a, col + a};
      vec.push_back(ch);
    }
  }
}

std::vector<CharPositions> WordSearchSolver::HelperLeft(
    const std::string& word) {
  std::vector<CharPositions> v;
  for (size_t i = 0; i < puzzle_height_; ++i) {
    std::string s;
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (word[0] == puzzle_[i][j]) {
        if (LocationInBounds(i + word.length() - 1,j - word.length() + 1) &&
            // If both direction are inbound  
            LocationInBounds(i - word.length() + 1, j + word.length() - 1)) {
          AddLeft(s, v, i, j, word, true);  // Try both direction, return if one
                                            // matches the input word
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
          AddLeft(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(
                       i + word.length() - 1,  // Row going down, col going up
                       j - word.length() + 1) &&
                   LocationInBounds(i - word.length() + 1,
                                    j + word.length() - 1)) {
          AddLeft(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(
                       i - word.length() + 1,  // Row going up, col going down
                       j + word.length() - 1) &&
                   LocationInBounds(i + word.length() - 1,
                                    j - word.length() + 1)) {
          AddLeft(s, v, i, j, word, true);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        }
      }
    }
  }
  return v;
}

void WordSearchSolver::AddHori(std::string& str,
                               std::vector<CharPositions>& vec, size_t row,
                               size_t col, const std::string& w, bool b) {
  if (b) {  // Add char with col going up
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row][col + a];
      CharPositions ch = {puzzle_[row][col + a], row, col + a};
      vec.push_back(ch);
    }
  } else {  // Add char with col going down
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row][col - a];
      CharPositions ch = {puzzle_[row][col - a], row, col - a};
      vec.push_back(ch);
    }
  }
}

std::vector<CharPositions> WordSearchSolver::HelperHorizontal(
    const std::string& word) {
  std::vector<CharPositions> v;
  for (size_t i = 0; i < puzzle_height_; ++i) {
    std::string s;
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (word[0] == puzzle_[i][j]) {
        if (LocationInBounds(
                i, j + word.length() - 1) &&  // If both direction are inbound
            LocationInBounds(i, j - word.length() + 1)) {
          AddHori(s, v, i, j, word, true);  // Try both direction, return if one
                                            // matches the input word
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
          AddHori(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(i, j + word.length() - 1) &&
                   LocationInBounds(i, j - word.length() + 1)) {
          AddHori(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(i, j - word.length() + 1) &&
                   LocationInBounds(i, j + word.length() - 1)) {
          AddHori(s, v, i, j, word, true);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        }
      }
    }
  }
  return v;
}

void WordSearchSolver::AddVec(std::string& str, std::vector<CharPositions>& vec,
                              size_t row, size_t col, const std::string& w,
                              bool b) {
  if (b) {  // Add char with row going up
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row + a][col];
      CharPositions ch = {puzzle_[row + a][col], row + a, col};
      vec.push_back(ch);
    }
  } else {  // Add char with row going down
    for (size_t a = 0; a < w.length(); ++a) {
      str += puzzle_[row - a][col];
      CharPositions ch = {puzzle_[row - a][col], row - a, col};
      vec.push_back(ch);
    }
  }
}

std::vector<CharPositions> WordSearchSolver::HelperVertical(
    const std::string& word) {
  std::vector<CharPositions> v;
  for (size_t i = 0; i < puzzle_height_; ++i) {
    std::string s;
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (word[0] == puzzle_[i][j]) {
        if (LocationInBounds(i + word.length() - 1,
                             j) &&  // If both direction are inbound
            LocationInBounds(i - word.length() + 1, j)) {
          AddVec(s, v, i, j, word, true);  // Try both direction, return if one
                                           // matches the input word
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
          AddVec(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(i + word.length() - 1, j) &&
                   LocationInBounds(i - word.length() + 1, j)) {
          AddVec(s, v, i, j, word, false);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        } else if (!LocationInBounds(i - word.length() + 1, j) &&
                   LocationInBounds(i + word.length() - 1, j)) {
          AddVec(s, v, i, j, word, true);
          if (s != word) {
            v.clear();
            s.clear();
          } else {
            return v;
          }
        }
      }
    }
  }
  return v;
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  std::vector<CharPositions> v;
  if (direction == CheckDirection::kHorizontal) {
    v = HelperHorizontal(word);
  } else if (direction == CheckDirection::kVertical) {
    v = HelperVertical(word);
  } else if (direction == CheckDirection::kRightDiag) {
    v = HelperRight(word);
  } else if (direction == CheckDirection::kLeftDiag) {
    v = HelperLeft(word);
  }
  if (v.empty()) {
    return WordLocation{};
  }
  return WordLocation{word, v};
}
