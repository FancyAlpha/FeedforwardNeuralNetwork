#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "MNISTReader.h"
#include "Matrix.h"
#include "MNISTPicture.h"
#include "FeedforwardNeuralNet.h"
#include "Stopwatch.hpp"

vector<vector<MNISTPicture>> createBatches(const vector<MNISTPicture> &trainingPics, const int batchSize);

int getNumCorrect(const vector<MNISTPicture> &testPics, FeedforwardNeuralNet &net);

using namespace std;


int main() {

    fstream trainImages("../data/training/train-images-idx3-ubyte/train-images.idx3-ubyte", ios::in | ios::binary);
    fstream trainLabels("../data/training/train-labels-idx1-ubyte/train-labels.idx1-ubyte", ios::in | ios::binary);


    fstream testImages("../data/test/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte", ios::in | ios::binary);
    fstream testLabels("../data/test/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte", ios::in | ios::binary);


    cout << "parsing data and creating images" << endl;


    // most of the hyper-parameters for this network are here
    const int epochs = 4;
    const int batchSize = 5;
    const double learningRate = 2;
    SigmoidNeuron hiddenNeuron{};
    SigmoidNeuron finalNeuron{};
    const int layerSizes[] = {784, 35, 10};
//    RegularRandom random(time(nullptr), -0.5, 0.5);
    NormalRandom random(time(nullptr));
    const int maxPictures = INT_MAX;

    MNISTReader dataParser{};
    vector<MNISTPicture> trainingPics = dataParser.getPictures(trainImages, trainLabels, maxPictures);
    vector<MNISTPicture> testPics = dataParser.getPictures(testImages, testLabels, maxPictures);

    FeedforwardNeuralNet net(layerSizes, sizeof(layerSizes) / sizeof(int), &hiddenNeuron, &finalNeuron, &random);

    cout << "creating batches of size " << batchSize << endl;

//    stopwatch::Stopwatch watch;

    for (int j = 0; j < epochs; j++) {
        // todo shuffle pictures here
        vector<vector<MNISTPicture>> batches = createBatches(trainingPics, batchSize);

        for (int i = 0; i < batches.size(); i++) {
            cerr << "\rbatch: (" << i + 1 << "/" << batches.size() << ")";
            net.learn(batches[i], learningRate);
        }

        int correctNum = getNumCorrect(testPics, net);
        cout << "\nepoch: " << j << " (" << correctNum << "/" << testPics.size() << ")" << endl;
    }

    trainImages.close();
    trainLabels.close();

    testImages.close();
    testLabels.close();

    return 0;
}


int getNumCorrect(const vector<MNISTPicture> &testPics, FeedforwardNeuralNet &net) {

    int correctNum = 0;
    for (int i = 0; i < testPics.size(); i++) {
        MNISTPicture pic = testPics[i];

        int res = net.predict(pic);
        if (res == pic.getClass()) {
            correctNum++;
        }
    }
    return correctNum;
}


vector<vector<MNISTPicture>> createBatches(const vector<MNISTPicture> &trainingPics, const int batchSize) {

    vector<vector<MNISTPicture>> batches;

    int numPicsUsed = 0;
    while (numPicsUsed < trainingPics.size()) {

        vector<MNISTPicture> batch;
        batch.reserve(batchSize);
        for (int i = 0; numPicsUsed < trainingPics.size() && i < batchSize; i++) {
            batch.push_back(trainingPics[numPicsUsed]);
            numPicsUsed++;
        }

        batches.push_back(batch);
    }
    return batches;
}
