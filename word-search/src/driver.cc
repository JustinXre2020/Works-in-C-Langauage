#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'t', 's', 'e', 'e', 'k', 's', 'q', 'h', 'l', 'e'},
                                        {'a', 'e', 'l', 'a', 'o', 'y', 'w', 'h', 'n', 'd'},
                                        {'r', 'w', 'h', 'o', 'm', 'y', 'e', 'u', 'j', 'c'},
                                        {'n', 't', 'a', 'h', 'u', 'g', 'm', 'g', 'h', 'v'},
                                        {'i', 'e', 'h', 'r', 'a', 'e', 'f', 'j', 'f', 'r'},
                                        {'s', 'i', 'm', 'h', 'r', 'i', 'l', 'h', 'd', 'f'},
                                        {'h', 'o', 'n', 'a', 'k', 'i', 't', 'd', 's', 'b'},
                                        {'e', 'p', 't', 's', 'j', 'p', 'o', 'h', 'e', 't'},
                                        {'d', 'e', 'q', 'f', 'g', 'k', 'i', 'r', 'z', 'n'},
                                        {'c', 'g', 'r', 'i', 'n', 'g', 'i', 'n', 'g', 'c'}};
  WordSearchSolver wss(puzzle);
 
  std::cout << wss.FindWord("enumerate") << std::endl;

  std::cout << wss.FindWord("tarnished") << std::endl;
  std::cout << wss.FindWord("warrior") << std::endl;
  std::cout << wss.FindWord("seeks") << std::endl;
  std::cout << wss.FindWord("elden") << std::endl;
  std::cout << wss.FindWord("ring") << std::endl;
}