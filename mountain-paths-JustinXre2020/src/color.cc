#include "color.hpp"
#include <iostream>

#define MAX 255
#define MIN 0
Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (b < MIN || r < MIN || g < MIN || b > MAX || r > MAX || g > MAX) {
    throw std::invalid_argument("Invalid input color.");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
