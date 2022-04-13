#include "student.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "course.hpp"
using namespace std;

int main() {
  Course c1 = {"IS 203", 3};
  Course c2 = {"IS 253", 3};
  Course c3 = {"IS 445", 3};
  vector<Course> v = {c1, c2, c3};
  // vector<Course> v = {};
  Student st1("Ike South", "000000000", "ike", "CS", v, false);
  st1.Graduate();
  cout << st1 << endl;
  return 0;
}
