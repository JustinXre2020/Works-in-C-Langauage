#include "student.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "course.hpp"

std::string Student::GetName() const { return name_; }

std::string Student::GetUIN() const { return uin_; }

std::string Student::GetNetId() const { return net_id_; }

std::string Student::GetMajor() const { return major_; }

bool Student::HasGraduated() const { return graduated_; }

const std::vector<Course>& Student::GetCourses() const { return courses_; }

void Student::SetName(std::string name) { name_ = name; }

void Student::SetMajor(std::string major) { major_ = major; }

bool Student::AddCourse(Course c) {
  for (Course cc : courses_) {
    if (cc.name == c.name && cc.credits == c.credits) {
      return false;
    }
  }
  courses_.push_back(c);
  return true;
}

int Student::Credits(const std::vector<Course>& c) const {
  int credit = 0;
  if (c.empty()) {
    return 0;
  }
  for (Course cc : c) {
    credit += cc.credits;
  }
  return credit;
}

void Student::Graduate() {
  if (Credits(courses_) >= min_credits_grad_) {
    graduated_ = true;
  } else {
    graduated_ = false;
  }
}

std::string Student::PrintCourses(const std::vector<Course>& c) const {
  std::string s;
  if (c.empty()) {
    return "";
  }
  for (Course cc : c) {
    if (cc.name == c.back().name && cc.credits == c.back().credits) {
      s += cc.name;
    } else {
      s += cc.name + ", ";
    }
  }
  return s;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << "Name: " << s.GetName() << '\n';
  os << "UIN: " << s.GetUIN() << '\n';
  os << "Net Id: " << s.GetNetId() << '\n';
  os << "Major: " << s.GetMajor() << '\n';
  os << "Credits: " << s.Credits(s.GetCourses()) << '\n';
  os << "Courses: " << s.PrintCourses(s.GetCourses()) << '\n';
  if (s.HasGraduated()) {
    os << "Graduated: True";
  } else {
    os << "Graduated: False";
  }
  return os;
}