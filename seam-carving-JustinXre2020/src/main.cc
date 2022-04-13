
#include <fstream>
#include <iostream>

#include "image_ppm.hpp"
#include "seam_carver.hpp"

using namespace std;
// void PrintUsage(const std::string& command) {
//   std::cout << "Usage: " << command << " INPUT_FILE [options] -o OUTPUT_FILE\n"
//             << "Options:\n"
//             << "\t-h times\tcarve times horizontal seams\n"
//             << "\t-v times\tcarve times vertical seams\n";
// }

// int main(int argc, char* argv[]) {
//   std::string out_option = "-o";
//   if (argc < 4 || out_option != argv[argc - 2]) {
//     PrintUsage(argv[0]);
//     return 1;
//   }

//   std::ifstream infile(argv[1]);
//   if (!infile.good()) {
//     std::cout << "file '" << argv[1] << "' not found" << std::endl;
//     return 1;
//   }

//   /* UNCOMMENT COMMENTED CODE BELOW AS YOU IMPLEMENT */

//   ImagePPM image;
//   infile >> image;
//   infile.close();

//   SeamCarver carver( image );
//   for ( int i = 2; i < argc - 2; i += 2 ) {
//     std::string times_string = argv[i + 1];
//     int times = 0;
//     try {
//       times = std::stoi( times_string );
//     } catch ( const std::exception& e ) {
//       std::cout << "Malformed option" << std::endl;
//       PrintUsage( argv[0] );
//       return 1;
//     }

//     std::string option = argv[i];
//     if ( option == "-h" ) {
//       for ( int t = 0; t < times; t++ ) {
//         carver.RemoveHorizontalSeam();
//       }
//     } else if ( option == "-v" ) {
//       for ( int t = 0; t < times; t++ ) {
//         carver.RemoveVerticalSeam();
//       }
//     } else {
//       std::cout << argv[i] << " not an option" << std::endl;
//       PrintUsage( argv[0] );
//       return 1;
//     }
//   }

//   std::ofstream outfile( argv[argc - 1] );
//   outfile << carver.GetImage();
//   outfile.close();
// }

int main() {
  ImagePPM image = ImagePPM("/home/vagrant/src/seam-carving-JustinXre2020/images/image1.ppm");
  SeamCarver seam = SeamCarver(image);
  for (int i = 0; i < seam.GetHeight(); ++i) {
    for (int j = 0; j < seam.GetWidth(); ++j) {
      cout << image.GetPixel(i, j).GetRed() << ' ' << image.GetPixel(i, j).GetGreen() << ' ' << image.GetPixel(i, j).GetBlue() << ' ';
    }
    cout << endl;
  }
  cout << "Above is the RGB value of image" << endl;

  int** energies = new int*[seam.GetHeight()];
  for (int i = 0; i < seam.GetHeight(); ++i) {
    energies[i] = new int[seam.GetWidth()];
    for (int j = 0; j < seam.GetWidth(); ++j) {
      energies[i][j] = seam.GetEnergy(i, j);
      cout << energies[i][j] << ' ';
    }
    cout << endl;
  }
  cout << seam.GetHeight() << endl;
  cout << seam.GetWidth() << endl;
  cout << "Above is the seam value of image" << endl;

  // int* arr = seam.GetHorizontalSeam();
  // for (int r = 0; r < seam.GetWidth(); ++r) {
  //   cout << arr[r] << endl;
  // }
  // cout << "Above is the Horizontal Seam of image" << endl;

  int* arr2 = seam.GetVerticalSeam();
  for (int r = 0; r < seam.GetHeight(); ++r) {
    cout << arr2[r] << endl;
  }
  cout << "Above is the Vertical Seam of image" << endl;

  // seam.RemoveVerticalSeam();
  // cout << seam.GetImage() << endl;
  // // int** energies2 = new int*[seam.GetHeight()];
  // // for (int i = 0; i < seam.GetHeight(); ++i) {
  // //   energies2[i] = new int[seam.GetWidth()];
  // //   for (int j = 0; j < seam.GetWidth(); ++j) {
  // //     energies2[i][j] = seam.GetEnergy(i, j);
  // //     cout << energies2[i][j] << ' ';
  // //   }
  // //   cout << endl;
  // // }
  // cout << seam.GetHeight() << endl;
  // cout << seam.GetWidth() << endl;
  // cout << "Above is the seam value of image after removed" << endl;

  
  // delete[] arr;
  delete[] energies;
  // delete[] energies2;
  delete[] arr2;
}
