#include <iostream>
#include <fstream>
#include "MNISTReader.h"
#include "Matrix.h"
#include "MNISTPicture.h"
#include "FeedforwardNeuralNet.h"
#include "Stopwatch.hpp"

using namespace std;

int main() {
    // the built files reside in cmake-build-debug
    fstream testImages("../data/test/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte", ios::in | ios::binary);
    fstream testLabels("../data/test/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte", ios::in | ios::binary);

    MNISTReader dataParser{};
    vector<MNISTPicture> pics = dataParser.getPictures(testImages, testLabels);

//    cout << pics[0] << endl;

    int batchSize = 10;
    int layerSizes[] = {28 * 28, 9, 10};

    FeedforwardNeuralNet net(layerSizes, 3);

    cout << "creating batches of size " << batchSize << endl;
    vector<vector<MNISTPicture>> batches;

    int numPicsUsed = 0;
    while (numPicsUsed < pics.size()) {

        vector<MNISTPicture> batch;
        for (int i = 0; numPicsUsed < pics.size() && i < batchSize; i++) {
            batch.push_back(pics[numPicsUsed]);
            numPicsUsed++;
        }

        batches.push_back(batch);
    }

    stopwatch::Stopwatch watch;
    cout << batches.size() << " batches created, moving to learning" << endl;
    for (int i = 0; i < batches.size(); i++) {
//        cout << batches[i][0] << endl;

        watch.start();
        double cost = net.learn(batches[i]);
        double elapsedTime = watch.elapsed();
        cout << "cost of batch " << i << " is " << cost << endl;
        cout << "took " << elapsedTime << "ms" << endl << endl;
    }

    cout << "learning done!" << endl;


//    for (int i = 0; i < pics.size(); i++) {
//        cout << net.predict(pics[i]) << endl;
//    }

    testImages.close();
    testLabels.close();

    return 0;
}