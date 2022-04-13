#include "path_image.hpp"

#include <cmath>
#include <iostream>


#define RED { 252, 25, 63 }
#define GREEN { 31, 253, 13 }

PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) {
  width_ = image.Width();
  height_ = image.Height();
  path_image_ = image.GetImage();
  std::vector<std::vector<int>> data = dataset.GetData();
  for (size_t row = 0; row < dataset.Height(); ++row) {
    Path p = {dataset.Width(), row};
    path_image_[row][0] = RED;
    p.SetLoc(0, row);
    size_t i = row;  // set a copy for the current row, used for changing rows in path traversal
    for (size_t j = 0; j < dataset.Width() - 1; ++j) {
      if (i == 0) {
        int min_value = Min(abs(data[i][j] - data[i + 1][j + 1]), 
                            abs(data[i][j] - data[i][j + 1]));
        if ((abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value) ||
            (abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) != min_value)) {
          path_image_[i][j + 1] = RED;
          p.SetLoc(j + 1, i);
        } else if (abs(data[i][j] - data[i][j + 1]) != min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value) {
          path_image_[i + 1][j + 1] = RED;
          p.SetLoc(j + 1, i + 1);
          i = i + 1;
        }
        p.IncEleChange(min_value);
      } else if (i == dataset.Height() - 1) {
        int min_value = Min(abs(data[i][j] - data[i - 1][j + 1]), 
                            abs(data[i][j] - data[i][j + 1]));
        if ((abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) == min_value) ||
            (abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) != min_value)) {
          path_image_[i][j + 1] = RED;
          p.SetLoc(j + 1, i);
        } else if (abs(data[i][j] - data[i][j + 1]) != min_value && abs(data[i][j] - data[i - 1][j + 1]) == min_value) {
          path_image_[i - 1][j + 1] = RED;
          p.SetLoc(j + 1, i - 1);
          i = i - 1;
        }
        p.IncEleChange(min_value);
      } else {
        PathTraverse(data, path_image_, p, i, j);
      }  // Parameter is: Grayscale image, image with paths, a path object, row, col
    }
    paths_.push_back(p);
  }
  Path min_ele_change = MinEleChange(paths_);
  for (size_t i = 0; i < min_ele_change.GetPath().size(); ++i) {
    size_t row = min_ele_change.GetPath()[i];
    path_image_[row][i] = GREEN;
  }
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (unsigned int i = 0; i < height_; ++i) {
    for (unsigned int j = 0; j < width_; ++j) {
      ofs << path_image_[i][j].Red() << " " << path_image_[i][j].Green() << " "
          << path_image_[i][j].Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}

void PathImage::PathTraverse(const std::vector<std::vector<int>>& data,
                             std::vector<std::vector<Color>>& path_image_,
                             Path& p, size_t& i, size_t j) {
  int min_value = Min(abs(data[i][j] - data[i + 1][j + 1]),
                      abs(data[i][j] - data[i][j + 1]),
                      abs(data[i][j] - data[i - 1][j + 1]));
  if ((abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) == min_value) ||
      (abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) != min_value && abs(data[i][j] - data[i - 1][j + 1]) == min_value) ||
      (abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) != min_value && abs(data[i][j] - data[i - 1][j + 1]) != min_value) ||
      (abs(data[i][j] - data[i][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) != min_value)) {
    path_image_[i][j + 1] = RED;
    p.SetLoc(j + 1, i);
  } else if ((abs(data[i][j] - data[i][j + 1]) != min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) == min_value) ||
             (abs(data[i][j] - data[i][j + 1]) != min_value && abs(data[i][j] - data[i + 1][j + 1]) == min_value && abs(data[i][j] - data[i - 1][j + 1]) != min_value)) {
    path_image_[i + 1][j + 1] = RED;
    p.SetLoc(j + 1, i + 1);
    i = i + 1;
  } else if (abs(data[i][j] - data[i - 1][j + 1]) == min_value && abs(data[i][j] - data[i + 1][j + 1]) != min_value && abs(data[i][j] - data[i][j + 1]) != min_value) {
    path_image_[i - 1][j + 1] = RED;
    p.SetLoc(j + 1, i - 1);
    i = i - 1;
  }
  p.IncEleChange(min_value);
}

int PathImage::Min(int a, int b, int c) {
  int min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  return min;
}

int PathImage::Min(int a, int b) {
  int min = a;
  if (b < min) {
    min = b;
  }
  return min;
}

Path PathImage::MinEleChange(const std::vector<Path>& paths) {
  Path min_change = paths[0];
  for (const Path& p : paths) {
    if (p.EleChange() < min_change.EleChange()) {
      min_change = p;
    }
  }
  return min_change;
}