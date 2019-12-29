#include <iostream>
#include <fstream>
#include "MNISTReader.h"
#include "Matrix.h"
#include "MNISTPicture.h"

using namespace std;

int main() {
    // the built files reside in cmake-build-debug
    fstream testImages("../data/test/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte", ios::in | ios::binary);
    fstream testLabels("../data/test/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte", ios::in | ios::binary);

    MNISTReader dataParser{};
    vector<MNISTPicture> pics = dataParser.getPictures(testImages, testLabels);

    for (int i = 0; i < pics.size(); i++) {
        cout << pics[i] << endl;
    }
//    if(testImages.is_open()) {
//        cout << "data file is open!" << endl;
//
//        uint32_t magic = 0;
//        dataFile.read((char*) &magic, sizeof(magic));
//        magic = magic;
//        cout << "magic num: " << magic << endl;
//
//        dataFile.read((char*) &magic, sizeof(magic));
//        magic = ~magic;
//        cout << "magic num2: " << magic << endl;
//    }
//
//    cout << "test finished!" << endl;
    testImages.close();
    testLabels.close();

////    MNISTReader mnistReader;
////    mnistReader.read();
//
//    Matrix mata(4, 3);
//    mata.set(0, 0, 1);
//    mata.set(0, 1, 2);
//    mata.set(0, 2, 3);
//    cout << mata << endl;
//
//    Matrix matb(4, 3);
//    matb.set(0, 2, 4);
//    matb.set(0, 3, 5);
//    matb.set(2, 3, 9);
//    cout << matb << endl;
//
//    cout << mata + matb << endl;
//
//    cout << endl;
//    MNISTPicture halp(28, 28);
//    halp.setPixel(0, 1);
//    halp.setPixel(1, 1);
//    halp.setPixel(2, 1);
//    halp.setPixel(3, 1);
//    halp.setPixel(783, 1);
//    cout << halp << endl;

    return 0;
}