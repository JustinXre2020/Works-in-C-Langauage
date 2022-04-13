#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <string>
#include <vector>
#include <map>

std::map<std::string, std::vector<std::string>> ConvertDNA(std::vector<std::string> v, std::map<std::string, std::vector<std::string>> m);
std::string FindPerson(std::map<std::string, std::vector<std::string>> m, std::string s); 

#endif