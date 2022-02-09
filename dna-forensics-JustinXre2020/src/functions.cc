#include "functions.hpp"
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, vector<string>> ConvertDNA(vector<string> v, map<string, vector<string>> m) {
  string key = v[0];
  v.erase(v.begin());
  m.insert(pair<string, vector<string>>(key, v));
  return m;
}

int Count(string s, string word) {
  int count = 0;
  int max = 0;
  while (s.find(word) != string::npos) {
    size_t current_index = s.find(word);
    count += 1;
    s.erase(current_index, word.length());
    if (current_index != s.find(word) && s.find(word) != string::npos) {
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

string FindPerson(map<string, vector<string>> m, string s) {
  vector<string> v_count;
  vector<string> v1;
  try
  {
    v1 = m.at("Names");
  }
  catch(const std::exception& e)
  {
    v1 = m.at("name");
  }
  for (unsigned int i = 0; i < v1.size(); ++i) {
    string word = v1[i];
    v_count.push_back(to_string(Count(s, word)));
  }
  int count_equal = 0;
  string person;
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
