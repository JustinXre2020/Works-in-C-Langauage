#include "seam_carver.hpp"
#include <iostream>
// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel left = {}; Pixel right = {}; Pixel up = {}; Pixel down = {};

  if (col - 1 < 0) {
    left = image_.GetPixel(row, width_ - 1);
  } else {
    left = image_.GetPixel(row, col - 1);
  }
  if (col + 1 == width_) {
    right = image_.GetPixel(row, 0);
  } else {
    right = image_.GetPixel(row, col + 1);
  }
  if (row - 1 < 0) {
    up = image_.GetPixel(height_ - 1, col);
  } else {
    up = image_.GetPixel(row - 1, col);
  }
  if (row + 1 == height_) {
    down = image_.GetPixel(0, col);
  } else {
    down = image_.GetPixel(row + 1, col);
  }

  int r_col = left.GetRed() - right.GetRed();
  int g_col = left.GetGreen() - right.GetGreen();
  int b_col = left.GetBlue() - right.GetBlue();
  int r_row = up.GetRed() - down.GetRed();
  int g_row = up.GetGreen() - down.GetGreen();
  int b_row = up.GetBlue() - down.GetBlue();

  return r_col * r_col + g_col * g_col + b_col * b_col + r_row * r_row + g_row * g_row + b_row * b_row;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** arr = new int*[height_];                          // Initialize an array with the energy
  for (int row = 0; row < height_; ++row) {
    arr[row] = new int[width_];
    for (int col = 0; col < width_; ++col) {
      arr[row][col] = GetEnergy(row, col);
    }
  }
  for (int col = width_ - 2; col >= 0; --col) {           // Calculating Horizontal seam
    for (int row = 0; row < height_; ++row) {
      if (row == 0) {
        arr[row][col] += MinTwo(arr[row][col + 1], arr[row + 1][col + 1]);
      } else if (row == height_ - 1) {
        arr[row][col] += MinTwo(arr[row - 1][col + 1], arr[row][col + 1]);
      } else {
        arr[row][col] += MinThree(arr[row - 1][col + 1], arr[row][col + 1], arr[row + 1][col + 1]);
      }
    }
  }
  int* horizontal_seam = new int[width_];                 // Initialize an array for Horizontal seam
  int min = arr[0][0];
  int record_row = 0;
  for (int row = 0; row < height_; ++row) {              
    if (arr[row][0] < min) {
      min = arr[row][0];
      record_row = row;
    }
  }
  horizontal_seam[0] = record_row;                        // Set the first row
  for (int col = 0; col < width_ - 1; ++col) {            // Traverse to get the rest of rows
    FindMinRow(arr, record_row, col);
    horizontal_seam[col + 1] = record_row;
  }
  for (int i = 0; i < height_; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
  return horizontal_seam;
}

int* SeamCarver::GetVerticalSeam() const {
  int** arr = new int*[height_];                          // Initialize an array with the energy
  for (int row = 0; row < height_; ++row) {
    arr[row] = new int[width_];
    for (int col = 0; col < width_; ++col) {
      arr[row][col] = GetEnergy(row, col);
    }
  }
  for (int row = height_ - 2; row >= 0; --row) {          // Calculating vertical seam
    for (int col = 0; col < width_; ++col) {
      if (col == 0) {
        arr[row][col] += MinTwo(arr[row + 1][col], arr[row + 1][col + 1]);
      } else if (col == width_ - 1) {
        arr[row][col] += MinTwo(arr[row + 1][col], arr[row + 1][col - 1]);
      } else {
        arr[row][col] += MinThree(arr[row + 1][col - 1], arr[row + 1][col], arr[row + 1][col + 1]);
      }
    }
  }
  int* vertical_seam = new int[height_];                      // Initialize an array for vertical seam
  int min = arr[0][0];
  int record_col = 0;
  for (int col = 0; col < width_; ++col) {
    if (arr[0][col] < min) {
      min = arr[0][col];
      record_col = col;
    }
  }
  vertical_seam[0] = record_col;                              // Set the first column
  for (int row = 0; row < height_ - 1; ++row) {               // Traverse to get the rest of columns
    FindMinCol(arr, record_col, row);
    vertical_seam[row + 1] = record_col;
  }
  for (int i = 0; i < height_; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
  return vertical_seam;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* arr = GetHorizontalSeam();
  auto** image = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; ++row) {
    image[row] = new Pixel[width_];
    for (int col = 0; col < width_; ++col) {    // Traverse each column to delete the seam row
      if (row >= arr[col]) {
        image[row][col] = image_.GetPixel(row + 1, col); 
      } else {
        image[row][col] = image_.GetPixel(row, col); 
      }
    }
  }
  ImagePPM new_image = ImagePPM(image, height_ - 1, width_, image_.GetMaxColorValue());
  image_.~ImagePPM();
  SetImage(new_image);
  delete[] arr;
}

void SeamCarver::RemoveVerticalSeam() {
  int* arr = GetVerticalSeam();
  auto** image = new Pixel*[height_];
  for (int row = 0; row < height_; ++row) {     // Traverse each row to delete the seam column
    image[row] = new Pixel[width_ - 1];
    for (int col = 0; col < width_ - 1; ++col) {   
      if (col >= arr[row]) {
        image[row][col] = image_.GetPixel(row, col + 1);
      } else {
        image[row][col] = image_.GetPixel(row, col);
      }
    }
  }
  ImagePPM new_image = ImagePPM(image, height_, width_ - 1, image_.GetMaxColorValue());
  image_.~ImagePPM();
  SetImage(new_image);
  delete[] arr;
}

int SeamCarver::MinTwo(int a, int b) const {
  int min = a;
  if (b < min) {
    min = b;
  }
  return min;
}

int SeamCarver::MinThree(int a, int b, int c) const {
  int min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  return min;
}

void SeamCarver::FindMinRow(int**& arr, int& record_row, int col) const {
  if (record_row == 0) {
    int min_value = MinTwo(arr[record_row][col + 1], arr[record_row + 1][col + 1]);
    if ((arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] != min_value) ||
        (arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] == min_value)) {
      return;
    } else {
      record_row += 1;
    }
  } else if (record_row == height_ - 1) {
    int min_value = MinTwo(arr[record_row - 1][col + 1], arr[record_row][col + 1]);
    if ((arr[record_row][col + 1] != min_value && arr[record_row - 1][col + 1] == min_value) ||
        (arr[record_row][col + 1] == min_value && arr[record_row - 1][col + 1] == min_value)) {  
      record_row -= 1;
    } else {
      return;
    }
  } else {
    int min_value = MinThree(arr[record_row - 1][col + 1], arr[record_row][col + 1], arr[record_row + 1][col + 1]);
    if ((arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] == min_value && arr[record_row - 1][col + 1] != min_value) ||
        (arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] != min_value && arr[record_row - 1][col + 1] == min_value) ||
        (arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] == min_value && arr[record_row - 1][col + 1] == min_value) ||
        (arr[record_row][col + 1] == min_value && arr[record_row + 1][col + 1] != min_value && arr[record_row - 1][col + 1] != min_value)) {
      return;
    } else if (arr[record_row][col + 1] != min_value  && arr[record_row + 1][col + 1] == min_value && arr[record_row - 1][col + 1] != min_value) {
      record_row += 1;
    } else {
      record_row -= 1;
    }
  }
}

void SeamCarver::FindMinCol(int**& arr, int& record_col, int row) const {
  if (record_col == 0) {
    int min_value = MinTwo(arr[row + 1][record_col + 1], arr[row + 1][record_col]);
    if ((arr[row + 1][record_col + 1] == min_value && arr[row + 1][record_col] == min_value) ||
        (arr[row + 1][record_col + 1] != min_value && arr[row + 1][record_col] == min_value)) {
      return;
    } else {
      record_col += 1;
    }
  } else if (record_col == width_ - 1) {
    int min_value = MinTwo(arr[row + 1][record_col - 1], arr[row + 1][record_col]);
    if ((arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] == min_value) ||
        (arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] != min_value)) {
      record_col -= 1;
    } else {
      return;
    }
  } else {
    int min_value = MinThree(arr[row + 1][record_col - 1], arr[row + 1][record_col], arr[row + 1][record_col + 1]);
    if ((arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] == min_value && arr[row + 1][record_col + 1] == min_value) ||
        (arr[row + 1][record_col - 1] != min_value && arr[row + 1][record_col] == min_value && arr[row + 1][record_col + 1] != min_value) ||
        (arr[row + 1][record_col - 1] != min_value && arr[row + 1][record_col] == min_value && arr[row + 1][record_col + 1] == min_value) ||
        (arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] == min_value && arr[row + 1][record_col + 1] != min_value)) {
      return;
    } else if ((arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] != min_value && arr[row + 1][record_col + 1] == min_value) ||
                (arr[row + 1][record_col - 1] == min_value && arr[row + 1][record_col] != min_value && arr[row + 1][record_col + 1] != min_value)) {
      record_col -= 1;
    } else {
      record_col += 1;
    }
  }
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image) : image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
