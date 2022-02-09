#include <iostream>
#include <cctype>
#include <fstream>
#include <map>
#include <string>
#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::ifstream ifs{argv[1]};
  std::map<std::string, std::vector<std::string>> map;
  for(std::string line; std::getline(ifs, line); line = "") 
    map = ConvertDNA(utilities::GetSubstrs(line, ','), map);

  std::cout << FindPerson(map, argv[2]) << std::endl;
  return 0;
}
