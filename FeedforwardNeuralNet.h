//
// Created by tarak on 12/27/2019.
//

#ifndef NEURALNETWORK_FEEDFORWARDNEURALNET_H
#define NEURALNETWORK_FEEDFORWARDNEURALNET_H


#include <vector>
#include "Layer.h"
#include "MNISTPicture.h"

class FeedforwardNeuralNet {

public:
    FeedforwardNeuralNet(int *, int);

    int predict(const MNISTPicture&);

private:
    vector<Layer> layers;
    vector<Matrix> activations;

    Matrix runNetwork(MNISTPicture);
    static int getMaxPos(Matrix);
};


#endif //NEURALNETWORK_FEEDFORWARDNEURALNET_H
