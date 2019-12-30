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
    cout << "finished parsing" << endl;

    for (int i = 0; i < pics.size(); i++) {
        cout << pics[i] << endl;
    }

    testImages.close();
    testLabels.close();

    return 0;
}