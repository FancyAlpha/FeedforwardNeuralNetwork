#include <iostream>
#include <fstream>
#include "MNISTReader.h"
#include "Matrix.h"
#include "MNISTPicture.h"
#include "FeedforwardNeuralNet.h"

using namespace std;

int main() {
    // the built files reside in cmake-build-debug
    fstream testImages("../data/test/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte", ios::in | ios::binary);
    fstream testLabels("../data/test/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte", ios::in | ios::binary);

    MNISTReader dataParser{};
    vector<MNISTPicture> pics = dataParser.getPictures(testImages, testLabels);


    cout << pics[0] << endl;

    int layerSizes[] = {28 * 28, 5, 5, 5, 10};

    FeedforwardNeuralNet net(layerSizes, 5);

    for (int i = 0; i < pics.size(); i++) {
        cout << net.predict(pics[i]) << endl;
    }

    testImages.close();
    testLabels.close();

    return 0;
}