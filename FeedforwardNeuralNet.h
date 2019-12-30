//
// Created by tarak on 12/27/2019.
//

#ifndef NEURALNETWORK_FEEDFORWARDNEURALNET_H
#define NEURALNETWORK_FEEDFORWARDNEURALNET_H


#include <vector>
#include "Layer.h"

class FeedforwardNeuralNet {

public:
    FeedforwardNeuralNet(int *layerHeights, int numLayers);

private:
    vector<Layer> layers;
    vector<Matrix> activations;
};


#endif //NEURALNETWORK_FEEDFORWARDNEURALNET_H
