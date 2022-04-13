#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <vector>

#include "course.hpp"

struct Student {
 private:
  std::string name_;
  std::string uin_;
  std::string net_id_;
  std::string major_;
  bool graduated_;
  std::vector<Course> courses_;
  static const int min_credits_grad_ = 120;

 public:
  Student(std::string name, std::string uin, std::string net_id) {
    name_ = name;
    uin_ = uin;
    net_id_ = net_id;
    major_ = "Undeclared";
    graduated_ = false;
  }
  Student(std::string name, std::string uin, std::string net_id,
          std::string major, std::vector<Course> courses, bool graduated) {
    name_ = name;
    uin_ = uin;
    net_id_ = net_id;
    major_ = major;
    graduated_ = graduated;
    courses_ = courses;
  }
  int Credits(const std::vector<Course>& c) const;
  std::string PrintCourses(const std::vector<Course>& c) const;
  std::string GetName() const;
  std::string GetUIN() const;
  std::string GetNetId() const;
  std::string GetMajor() const;
  bool HasGraduated() const;
  const std::vector<Course>& GetCourses() const;
  void SetName(std::string name);
  void SetMajor(std::string major);
  bool AddCourse(Course c);
  void Graduate();
};

std::ostream& operator<<(std::ostream& os, const Student& s);

#endif