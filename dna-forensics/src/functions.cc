#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>


std::map<std::string, std::vector<std::string>> ConvertDNA(std::vector<std::string> v, std::map<std::string, std::vector<std::string>> m) {
  std::string key = v[0];
  v.erase(v.begin());
  m.insert(std::pair<std::string, std::vector<std::string>>(key, v));
  return m;
}

int Count(std::string s, std::string word) {
  int count = 0;
  int max = 0;
  while (s.find(word) != std::string::npos) {
    size_t current_index = s.find(word);
    count += 1;
    s.erase(current_index, word.length());
    if (current_index != s.find(word) && s.find(word) != std::string::npos) {
      if (max < count) {
        max = count;
        count = 0;
      }
    }
  }
  if (count > max) {
    return count;
  }
  return max;
}

std::string FindPerson(std::map<std::string, std::vector<std::string>> m, std::string s) {
  std::vector<std::string> v_count;
  std::vector<std::string> v1;
  try
  {
    v1 = m.at("Names");
  }
  catch(const std::exception& e)
  {
    v1 = m.at("name");
  }
  for (unsigned int i = 0; i < v1.size(); ++i) {
    std::string word = v1[i];
    v_count.push_back(std::to_string(Count(s, word)));
  }
  int count_equal = 0;
  std::string person;
  for (auto const& element : m) {
    if (element.second == v_count) {
      count_equal += 1;
      person += element.first;
    }
  }
  if (count_equal == 1) {
    return person;
  }
  return "No match";
}
