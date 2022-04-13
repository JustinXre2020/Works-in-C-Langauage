#include "illini_book.hpp"
#include "utilities.hpp"
#include <iostream>

int main() {
  IlliniBook students = {"/home/vagrant/src/mp-illini-book-JustinXre2020/example/persons.csv", "/home/vagrant/src/mp-illini-book-JustinXre2020/example/relations.csv"};
  std::cout << students << std::endl;
  bool b = students.AreRelated(1, 6);
  std::cout <<  "AreRelated tests: " << b << std::endl;
  bool c = students.AreRelated(1, 3);
  std::cout <<  "AreRelated tests: " << c << std::endl;
  bool d = students.AreRelated(11, 13);
  std::cout <<  "AreRelated tests: " << d << std::endl;
  bool e = students.AreRelated(27, 29);
  std::cout <<  "AreRelated tests: " << e << std::endl;
  bool f = students.AreRelated(11, 19);
  std::cout <<  "AreRelated tests: " << f << std::endl;
  bool g = students.AreRelated(37, 43);
  std::cout <<  "AreRelated tests: " << g << std::endl;
  std::cout <<  "GetRelated tests: " << students.GetRelated(1, 2) << std::endl;
  std::cout <<  "GetRelated tests: " << students.GetRelated(1, 4) << std::endl;
  std::cout <<  "GetRelated tests: " << students.GetRelated(1, 6, "128") << std::endl;
  std::cout <<  "GetRelated tests: " << students.GetRelated(1, 6, "124") << std::endl;
  std::cout <<  "GetRelated tests: " << students.GetRelated(1, 9, "124") << std::endl;

  for (int i : students.GetSteps(7, 3)) 
    std::cout <<  "GetSteps tests: " << i << std::endl;
  std::cout << "CountGroups tests: "  << std::endl << students.CountGroups() << std::endl;
  std::cout << "CountGroups tests: "  << std::endl << students.CountGroups("124") << std::endl;
  std::cout << "CountGroups tests: "  << std::endl << students.CountGroups("173") << std::endl;
  std::cout << "CountGroups tests: "  << std::endl << students.CountGroups(std::vector<std::string>{ "128", "173" }) << std::endl;
  return 0;
}
