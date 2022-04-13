#ifndef PATH_IMAGE_HPP
#define PATH_IMAGE_HPP

#include <string>
#include <cstdlib>  // for size_t
#include <vector>

#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include "color.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;	
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;	
  void ToPpm(const std::string& name) const;
  int Min(int a, int b, int c);
  int Min(int a, int b);
  Path MinEleChange(const std::vector<Path>& paths);
  void PathTraverse(const std::vector<std::vector<int>>& data, std::vector<std::vector<Color>>& path_image_, Path& p, size_t& i, size_t j); 

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif