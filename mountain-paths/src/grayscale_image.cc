#include "grayscale_image.hpp"

#include <iostream>

#include "color.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  for (size_t i = 0; i < dataset.Height(); ++i) {
    std::vector<Color> v;
    for (size_t j = 0; j < dataset.Width(); ++j) {
      double d = 0.0;
      if (dataset.MaxEle() != dataset.MinEle()) {
        d = (double)(dataset.DatumAt(i, j) - dataset.MinEle()) /
            (double)(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue;
      }
      int shade_of_gray = (int)std::round(d);
      v.push_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
    }
    image_.push_back(v);
  }
  width_ = dataset.Width();
  height_ = dataset.Height();
}
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width,
                               size_t height) {
  ElevationDataset dataset = ElevationDataset(filename, width, height);
  for (size_t i = 0; i < dataset.Height(); ++i) {
    std::vector<Color> v;
    for (size_t j = 0; j < dataset.Width(); ++j) {
      double d = 0.0;
      if (dataset.MaxEle() != dataset.MinEle()) {
        d = (double)(dataset.DatumAt(i, j) - dataset.MinEle()) /
            (double)(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue;
      }
      int shade_of_gray = (int)std::round(d);
      v.push_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
    }
    image_.push_back(v);
  }
  width_ = dataset.Width();
  height_ = dataset.Height();
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_[row][col];
}
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{name};
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (unsigned int i = 0; i < height_; ++i) {
        for (unsigned int j = 0; j < width_; ++j) {
            ofs << image_[i][j].Red() << " " << image_[i][j].Green() << " " << image_[i][j].Blue() << " ";
        }
        ofs << std::endl;
    }
    ofs.close();
}