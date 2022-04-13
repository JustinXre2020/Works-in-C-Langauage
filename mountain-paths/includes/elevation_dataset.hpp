#ifndef ELEVATION_DATASET_HPP
#define ELEVATION_DATASET_HPP

#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <fstream>

class ElevationDataset {
public:
  // write behavior declarations here; define in elevation_dataset.cc.
  ElevationDataset(const std::string& filename, size_t width, size_t height);
  size_t Width() const;
  size_t Height() const;
  int MaxEle() const;
  int MinEle() const;
  int DatumAt(size_t row, size_t col) const;
  const std::vector<std::vector<int>>& GetData() const;
  bool IntCheck(const std::string& value);
private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
};

#endif