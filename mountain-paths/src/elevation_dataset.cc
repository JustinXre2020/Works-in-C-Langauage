#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename, size_t width,
                                   size_t height) {
  std::ifstream ifs{filename};
  std::vector<int> v;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::string value;
    size_t count = 0;
    for (size_t i = 0; i < line.length(); ++i) {
      if (line.at(i) == ' ') {
        count = i + 1;
        if (!value.empty() && IntCheck(value)) {
          v.push_back(std::stoi(value));
          value.clear();
        }
      } else {
        value += line.at(i);
      }
    }
    if ( IntCheck(line.substr(count, line.length() - count)) ) {
      v.push_back(std::stoi(line.substr(count, line.length() - count)));
    }
  }
  if (v.size() != height * width) 
    throw std::runtime_error("Size is not correct");
  std::vector<int> sub_vec;
  for (size_t i = 0; i < v.size(); ++i) {
    sub_vec.push_back(v[i]);
    if ( (i + 1) % width == 0 ) {
      data_.push_back(sub_vec);
      sub_vec.clear();
    }
  }
  
  // std::ifstream ifs{filename};
  // if (!ifs.is_open()) throw std::runtime_error("Invalid");
  // int value = 0;
  // for (size_t i = 0; i < height; ++i) {
  //   std::vector<int> temp;
  //   for (size_t j = 0; j < width; ++j) {
  //     if (!(ifs >> value)) {
  //       throw std::runtime_error("Not good");
  //     }
  //     temp.push_back(value);
  //   }
  //   data_.push_back(temp);
  // }
  // if (ifs >> value) throw std::runtime_error("Invalid");

  width_ = width;
  height_ = height;
  int max = data_[0][0];
  int min = data_[0][0];
  for (size_t i = 0; i < data_.size(); ++i) {
    for (size_t j = 0; j < data_[0].size(); ++j) {
      if (data_[i][j] > max) max = data_[i][j];
      if (data_[i][j] < min) min = data_[i][j];
    }
  }
  max_ele_ = max;
  min_ele_ = min;
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}

bool ElevationDataset::IntCheck(const std::string& value) {
  try {
    std::stoi(value);
    return true;
  } catch (const std::exception& e) {
    return false;
  }
}
