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


    fstream trainImages("../data/training/train-images-idx3-ubyte/train-images.idx3-ubyte", ios::in | ios::binary);
    fstream trainLabels("../data/training/train-labels-idx1-ubyte/train-labels.idx1-ubyte", ios::in | ios::binary);


    cout << "parsing data and creating images" << endl;
    MNISTReader dataParser{};
    vector<MNISTPicture> trainingPics = dataParser.getPictures(trainImages, trainLabels);

    const int epochs = 20;
    const int batchSize = 10;
    int layerSizes[] = {dataParser.width() * dataParser.height(), 16, 16, 10};

    FeedforwardNeuralNet net(layerSizes, sizeof(layerSizes) / sizeof(int));

    cout << "creating batches of size " << batchSize << endl;
    vector<vector<MNISTPicture>> batches;

    int numPicsUsed = 0;
    while (numPicsUsed < trainingPics.size()) {

        vector<MNISTPicture> batch;
        for (int i = 0; numPicsUsed < trainingPics.size() && i < batchSize; i++) {
            batch.push_back(trainingPics[numPicsUsed]);
            numPicsUsed++;
        }

        batches.push_back(batch);
    }

    stopwatch::Stopwatch watch;
    cout << batches.size() << " batches created, moving to learning" << endl;

    for (int j = 0; j < epochs; j++) {
        for (int i = 0; i < batches.size(); i++) {

//        watch.start();
            double cost = net.learn(batches[i], 3);
            cerr << "\r(" << j << "/" << batches.size() << ")";
//        double elapsedTime = watch.elapsed();
//        cout << "cost of batch " << i << " is " << cost << endl;
//        cout << "(" << i << ", " << batches.size() << ")" << elapsedTime << "ms" << endl << endl;
        }

//        cerr << endl;
    }

    cout << "\rlearning done!" << endl;

    trainImages.close();
    trainLabels.close();

    cout << "moving to testing" << endl;

    fstream testImages("../data/test/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte", ios::in | ios::binary);
    fstream testLabels("../data/test/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte", ios::in | ios::binary);

    vector<MNISTPicture> testPics = trainingPics;//dataParser.getPictures(testImages, testLabels);

    int correctNum = 0;
    for (int i = 0; i < testPics.size(); i++) {
        MNISTPicture pic = testPics[i];

        int res = net.predict(pic);
        if (res == pic.getClass()) {
            correctNum++;
        } else {
//            cout << pic << endl;
//            cout << "predicted: " << res << ", actual: " << pic.getClass() << endl;
        }
    }

    testImages.close();
    testLabels.close();

    cout << "(" << correctNum << "/" << testPics.size() << ") " <<
         ((double) correctNum / testPics.size()) * 100 << "% correct" << endl;
    cout << "testing done!" << endl;
    return 0;
}