//
// Created by tarak on 12/27/2019.
//

#include <iostream>
#include "FeedforwardNeuralNet.h"
#include "Neuron.h"

FeedforwardNeuralNet::FeedforwardNeuralNet(int *layerHeights, int numLayers) {

    for (int i = 1; i < numLayers; i++) {
        // passing in the arguments of the constructor of the object we want to make is enough
        layers.emplace_back(layerHeights[i - 1], layerHeights[i]);
    }
}

Matrix FeedforwardNeuralNet::runNetwork(MNISTPicture picture) {
    activations.clear();

    Matrix picMat = picture.getData();
    activations.push_back(picMat);
//    cout << "there are " << layers.size() << " layers" << endl;
//    cout << "curr activation is " << picMat.width() << "x" << picMat.height() << endl << endl;
//    cout << picMat << endl;
//    cout << curr << endl;
    for (int i = 0; i < layers.size(); i++) {
//        cout << "going through layer " << i
//             << endl; // << " (" << layers[i].weights.width() << "x" << layers[i].weights.height() << ")" << endl;

//        cout << layers[i] << endl;
//        cout << "weights" << endl;
//        cout << layers[i].weights;

        Matrix newCurr = Neuron::sigmoidFunction(layers[i].feedforward(activations.back()));

//        cout << "new activation" << endl;
//        cout << newCurr << endl;
        activations.push_back(newCurr);
    }

    return activations.back();
}

int FeedforwardNeuralNet::predict(const MNISTPicture &picture) {
    return getMaxPos(runNetwork(picture));
}

// pre: mat is a column vector
int FeedforwardNeuralNet::getMaxPos(Matrix mat) {

    int maxPos = -1;
    double maxVal = DBL_MIN;
    for (int r = 0; r < mat.height(); r++) {
        double matVal = mat.get(r, 0);
        if (matVal >= maxVal) {
            maxVal = matVal;
            maxPos = r;
        }
    }

    return maxPos;
}
