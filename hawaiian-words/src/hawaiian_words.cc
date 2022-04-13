#include <iostream>
#include <string>
#include <vector>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::vector<char> vec = {'a', 'e', 'i', 'o', 'u', 'p',
                           'k', 'h', 'l', 'm', 'n', 'w'};
  std::string phon;
  for (int i = 0; i < argc; ++i) {
    std::string word = argv[i];
    std::string phonetics = ConvertHawaiian(word, vec, phon);
    std::cout << phonetics << std::endl;
  }
}