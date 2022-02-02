#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Your function definitions should go in this source file.
std::string HelperI(std::string ph, std::string row, unsigned int index,
                    int vowelgroup) {
  if (vowelgroup == 0) {
    if (std::tolower(row[index - 1]) == 'a') {
      ph.resize(ph.size() - 3);
      ph += "eye-";
    } else if (std::tolower(row[index - 1]) == 'e' ||
               std::tolower(row[index - 1]) == 'u') {
      ph.resize(ph.size() - 3);
      ph += "ay-";
    } else if (std::tolower(row[index - 1]) == 'o') {
      ph.resize(ph.size() - 3);
      ph += "oy-";
    } else {
      ph += "ee-";
    }
  } else {
    ph += "ee-";
  }
  return ph;
}

std::string HelperU(std::string ph, std::string row, unsigned int index,
                    int vowelgroup) {
  if (vowelgroup == 0) {
    if (std::tolower(row[index - 1]) == 'a' ||
        std::tolower(row[index - 1]) == 'o') {
      ph.resize(ph.size() - 3);
      ph += "ow-";
    } else if (std::tolower(row[index - 1]) == 'e') {
      ph.resize(ph.size() - 3);
      ph += "eh-oo-";
    } else {
      ph += "oo-";
    }
  } else {
    ph += "oo-";
  }
  return ph;
}

std::string HelperO(std::string ph, std::string row, unsigned int index,
                    int vowelgroup) {
  if (vowelgroup == 0) {
    if (std::tolower(row[index - 1]) == 'a') {
      ph.resize(ph.size() - 3);
      ph += "ow-";
      return ph;
    }
  }
  ph += "oh-";
  return ph;
}

std::string HelperW(std::string ph, std::string row, unsigned int index) {
  if (index == 0) {
    ph += 'w';
  } else {
    unsigned char pre = std::tolower(row[index - 1]);
    if (pre == 'i' || pre == 'e') {
      ph += 'v';
    } else {
      ph += 'w';
    }
  }
  return ph;
}

std::string HelperMain(std::string pho, unsigned char input, std::string row,
                       unsigned int index, int vowel_count) {
  int vowelgroup = vowel_count % 2;
  if (input == 'a') {
    pho += "ah-";
  } else if (input == 'e') {
    if (vowelgroup == 0) {
      if (std::tolower(row[index - 1]) == 'a') {
        pho.resize(pho.size() - 3);
        pho += "eye-";
      } else {
        pho += "eh-";
      }
    } else {
      pho += "eh-";
    }
  } else if (input == 'i') {
    return HelperI(pho, row, index, vowelgroup);
  } else if (input == 'u') {
    return HelperU(pho, row, index, vowelgroup);
  } else if (input == 'o') {
    return HelperO(pho, row, index, vowelgroup);
  }
  return pho;
}

std::string ConvertHawaiian(std::string str, std::vector<char> v,
                            std::string phonetics) {
  int vowel_count = 0;
  for (unsigned int j = 0; j < str.length(); ++j) {
    if (str[j] == '\'' || str[j] == ' ') {
      if (phonetics.back() == '-') {
        phonetics.resize(phonetics.size() - 1);
      }
      phonetics += str[j];
      continue;
    }
    bool hawaiian_char = false;
    unsigned char c = std::tolower(str[j]);
    for (unsigned int a = 0; a < v.size(); ++a) {
      if (v[a] == c) {
        hawaiian_char = true;
      }
    }
    if (!(hawaiian_char)) {
      std::string not_part =
          str + " contains a character not a part of the Hawaiian language.";
      return not_part;
    } else {
      if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' ||
          c == 'n') {
        phonetics += c;
        vowel_count = 0;
      } else if (c == 'w') {
        phonetics = HelperW(phonetics, str, j);
        vowel_count = 0;
      } else {
        vowel_count += 1;
        phonetics = HelperMain(phonetics, c, str, j, vowel_count);
      }
    }
  }
  if (phonetics.back() == '-') {
    phonetics.resize(phonetics.size() - 1);
  }
  return phonetics;
}
