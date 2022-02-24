#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'c', 'h', 'a', 'o', 't'},
                                        {'t', 'e', 'l', 'a', 'o'},
                                        {'a', 'h', 'h', 'o', 'm'},
                                        {'c', 't', 'a', 'h', 'u'},
                                        {'y', 'e', 'h', 'o', 'a'}};
  WordSearchSolver wss(puzzle);
 
  std::cout << wss.FindWord("ohh");
}