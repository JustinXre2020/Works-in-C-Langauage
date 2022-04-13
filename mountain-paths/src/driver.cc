#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main() {
    ElevationDataset e1 = {"/home/vagrant/src/mp-mountain-paths-JustinXre2020/example-data/ex_input_data/map-input-w51-h55.dat", 51, 55};
    // GrayscaleImage g1 = {e1};
    // GrayscaleImage g1 = {"/home/vagrant/src/mp-mountain-paths-JustinXre2020/example-data/ex_input_data/map-input-w51-h55.dat", 51, 55};
    // PathImage p1 = {g1, e1};
    for (size_t i = 0; i < e1.GetData().size(); ++i) {
        for (size_t j = 0; j < e1.GetData()[i].size(); ++j) {
            cout << e1.GetData()[i][j] << endl;
        }
    }
    cout << "-----------------------Above is the Path images-----------------------" << endl;
    // Path p = p1.Paths()[32];
    // for (size_t i = 0; i < p.GetPath().size(); ++i)
    //     cout << p.GetPath()[i] << ' ';
    // cout << endl;
    cout << e1.MaxEle() << endl;
    cout << e1.MinEle() << endl;
    cout << e1.Width() << endl;
    cout << e1.Height() << endl;

}
